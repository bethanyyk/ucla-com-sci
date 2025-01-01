from sys import argv

def read_fasta(fasta):
    ''' Reads the FASTA file and returns a concatenated sequence '''
    with open(fasta, 'r') as file:
        lines = file.readlines()

    # Remove header lines that start with '>'
    for line in lines:
        if line[0] == '>':
            lines.remove(line)

    sequence = ""
    for line in lines:
        sequence += line.strip()
    return sequence

def read_codon_table(table):
    ''' Reads the codon table file and returns a dictionary mapping codons to amino acids '''
    with open(table, 'r') as file:
        lines = [line.strip() for line in file if line.strip()]
    
    codons = {}
    for line in lines:
        columns = line.split()
        codon = columns[0]
        amino_acid = columns[1]
        codons[codon] = amino_acid
    return codons

def get_reading_frames(sequence):
    ''' Get all possible reading frames '''
    reading_frames = []

    # Get the 3 reading frames on the forward strand
    reading_frames.append(sequence.upper())
    reading_frames.append(sequence.upper()[1:])
    reading_frames.append(sequence.upper()[2:])

    # Get the 3 reading frames on the reverse strand
    complement = {'A': 'T', 'T': 'A', 'G': 'C', 'C': 'G'}
    reverse_complement = ""
    for i in sequence[::-1]:
        nt = i.upper()
        base = complement[nt]
        reverse_complement += base
    reading_frames.append(reverse_complement)
    reading_frames.append(reverse_complement[1:])
    reading_frames.append(reverse_complement[2:])

    return reading_frames

def translate_sequence(reading_frames, codons):
    ''' Translates each sequence in a list of sequences into an amino acid sequence using a codon dictionary '''
    transcripts = []
    for seq in reading_frames:
        transcript = []
        for i in range(0, len(seq) -2, 3):
            codon = seq[i:i+3].upper()
            amino_acid = codons[codon]
            transcript.append(amino_acid)      
        transcripts.append(transcript)
    return transcripts

def valid_transcripts(transcripts):
    ''' Determines whether the transcript contains a valid transcript based on start and stop codons '''
    valid_transcripts = []
    for transcript in transcripts:
        transcript_string = ''.join(transcript)
        while 'M' in transcript_string and '-' in transcript_string:
            start = transcript_string.find('M')
            stop = transcript_string.find('-', start)
            valid_transcripts.append(transcript_string[start:stop+1])
            transcript_string = transcript_string[start+1:]
    return valid_transcripts

def main():
    fasta_file = argv[1]
    table_file = argv[2]

    sequence = read_fasta(fasta_file)
    codon_table = read_codon_table(table_file)
    reading_frames = get_reading_frames(sequence)
    transcripts = translate_sequence(reading_frames, codon_table)
    valid = valid_transcripts(transcripts)

    for transcript in valid:
        print(transcript)

if __name__ == "__main__":
    main()
