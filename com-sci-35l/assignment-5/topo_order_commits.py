#!/usr/local/cs/bin/python3

import os
import sys
import zlib

class CommitNode:
    ''' Each commit can be represented as an instance of the CommitNode class '''
    def __init__(self, commit_hash):
        """
        :type commit_hash: str
        """
        self.commit_hash = commit_hash
        self.parents = set()
        self.children = set()

def parse_object(repo_path, commit_hash):
    object_path = os.path.join(repo_path, "objects")
    object_path = os.path.join(object_path, commit_hash[:2], commit_hash[2:])

    with open(object_path, 'rb') as f:
        compressed_data = f.read()

    decompressed_data = zlib.decompress(compressed_data)
    object_content = decompressed_data.decode('utf-8')

    return object_content

def get_parents(object_content):
    parents = []
    lines = object_content.split("\n")
    for line in lines:
        if line[:6] == "parent":
            words = line.split()
            parents.append(words[1].rstrip("\n"))
    return parents

def topo_order_commits():
    ''' Discover the .git directory '''
    curr_directory = os.getcwd()

    while True:
        if os.path.isdir(os.path.join(curr_directory, ".git")):
            curr_directory = os.path.join(curr_directory, ".git")
            break
        
        # .git cannot be found when the search went all the way up to the root directory
        if curr_directory == "/":
            sys.stderr.write('Not inside a Git repository')
            exit(1)
        
        curr_directory = os.path.dirname(curr_directory)

    repo_path = curr_directory
    root_commits = []
    hash_to_branch = {}
    graph = {}

    ''' Get the list of local branch names'''
    heads_path = os.path.join(repo_path, "refs/heads")

    queue = []
    queue.append('')
    root_commit_hashes = []

    # Breadth-first search - Traverse nodes at present depth before moving on to next depth level
    while queue:
        popped = queue.pop(0) # Current subdirectory being traversed
        branches_path = os.path.join(heads_path, popped)

        for file in os.listdir(branches_path):
            file_path = os.path.join(branches_path, file)

            # If it's another subdirecory, add to queue for further traversal
            if os.path.isdir(file_path):
                queue.append(file + "/")
                continue

            # If it's a file, read the commit hash that represents the branch's head
            with open(file_path, 'r') as head_file:
                commit_hash = head_file.read().strip()
            root_commit_hashes.append(commit_hash)
            node = CommitNode(commit_hash)
            graph[commit_hash] = node
            root_commits.append(node)

            # If the commit hash is already associated with other branches, append the current branch to the list
            branch_name = os.path.join(popped, file)
            if commit_hash not in hash_to_branch.keys():
                hash_to_branch[commit_hash] = [branch_name]
            else:
                hash_to_branch[commit_hash].append(branch_name)

    ''' Build the commit graph '''
    stack = root_commit_hashes[:]

    # Iterative depth-first search - Traverse an entire branch before backtracking
    while stack:
        child_hash = stack.pop() # Current commit being processed
        parents = get_parents(parse_object(repo_path, child_hash))
        parents.sort()

        for parent_hash in parents:
            # If the parent commit isn't already in the graph, create a new CommitNode and add it to the graph
            if parent_hash not in graph:
                graph[parent_hash] = CommitNode(parent_hash)

            # If the child_hash is not already listed in the parent_hash's children set
            if graph[child_hash] not in graph[parent_hash].children:
                graph[child_hash].parents.add(graph[parent_hash]) # Add the parent_hash's CommitNode to the parents set of the child_hash
                graph[parent_hash].children.add(graph[child_hash]) # Add the child_hash's CommitNode to the children set of the parent_hash
                stack.append(parent_hash) # Push parent_hash onto the stack so it can be processed as a child or its own parents later
    
    ''' Generate a topological ordering of the commits in the graph '''
    # Kahn's algorithm
    L = []

    incoming_edges = {}
    for commit_hash, node in graph.items():
        incoming_edges[commit_hash] = len(node.children)

    S = []
    for commit_hash, e in incoming_edges.items():
        if e == 0:
            S.append(commit_hash)

    while S: # while S is not empty do 
        n = S.pop(0) # remove a node n from S
        L.append(n) # add n to L

        parents = get_parents(parse_object(repo_path, n))
        for m in parents: # for each node m with an edge e from n to m do
            incoming_edges[m] -= 1 # remove edge e from the graph
            if incoming_edges[m] == 0: # if m has no other incoming edges then
                S.append(m) # insert m into S
                S.sort()

    topological_ordering = L

    ''' Print the commit hashes in the order generated by the previous step, from the least to the greatest '''
    sticky_created = False

    for i in range(len(topological_ordering)):
        # If we are about to print a commit that is part of a sticky end
        if sticky_created is True:
            sticky_created = False # Reset sticky_created
            print("=", end="")
            children_nodes = graph[topological_ordering[i]].children # Gather the commit hashes of the children
            children = []
            for node in children_nodes:
                children.append(node.commit_hash)
            print(*children)
        print(topological_ordering[i], end="") # Print the current commit hash without a newline

        # If the current commit is associated with one or more brances
        if topological_ordering[i] in hash_to_branch:
            branches_for_commit = hash_to_branch[topological_ordering[i]] # Get the list of branches for the current commit
            branches_for_commit.sort()
            print(" ", end="")
            print(*branches_for_commit, end="")
        print()

        # If the current commit is the last one in the list
        if i == len(topological_ordering) - 1:
            break

        # If the next commit is a parent of the current commit
        parents = get_parents(parse_object(repo_path, topological_ordering[i]))
        if topological_ordering[i + 1] not in parents:
            sticky_created = True # Set sticky_created
            print(*parents, end="")
            print("=\n")

if __name__ == "__main__":
    topo_order_commits()

'''
Used strace to verify that my implementation doesn't use other commands by making sure there were no subprocess calls
'''
