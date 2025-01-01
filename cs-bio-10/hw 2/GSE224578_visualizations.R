library(DESeq2)
library(RColorBrewer)
library(gplots)
library(ggplot2)

# Normalization - Reads per million (RpM) ######################################

# expression <- read.table("GSE224578_MN_5vs5_edgeR_counts2.txt", header = TRUE, row.names = 1, sep = "\t")
# normalized <- expression
# for (i in 1:10) {
#   normalized[,i] <- 1000000 * normalized[,i] / sum(normalized[,i])  
# }
# 
# p_values <- matrix(nrow = 63111)
# for (i in 1:63111) {
#   p_values[i,1] <- wilcox.test(HC[i,], ATXN2[i,])[[3]]
# }
# p_values <- as.data.frame(p_values)
# row.names(p_values) <- row.names(expression)
# p_values[,2] <- p_values[,1] * 63111
# colnames(p_values)[2] <- "Bonferroni"

# DESeq ########################################################################

library(DESeq2)
raw_counts <- read.table("GSE224578_MN_5vs5_edgeR_counts2.txt", header = TRUE, row.names = 1, sep = "\t")
characteristic <- as.data.frame(c(rep("Healthy control", length.out = 5), rep("genotype: ATXN2 intermediate repeat expansions", length.out = 5)))
row.names(characteristic) <- colnames(raw_counts)
colnames(characteristic)[1] <- "characteristic"
DESeq <- DESeqDataSetFromMatrix(countData = raw_counts, colData = characteristic, design = ~characteristic)
DESeq <- DESeq(DESeq)
results <- results(DESeq)
gene_stats <- as.data.frame(results@listData)
row.names(gene_stats) <- results@rownames

table(gene_stats$padj < 0.05)
# 62 significantly differentially expressed genes

# Formatting for ggplot2 #######################################################

expression <- read.table("GSE224578_MN_5vs5_edgeR_counts2.txt", header = TRUE, row.names = 1, sep = "\t")
characteristic <- as.data.frame(t(c(rep("Healthy control", length.out = 5), rep("genotype: ATXN2 intermediate repeat expansions", length.out = 5))))
colnames(characteristic) <- colnames(expression)
row.names(characteristic) <- "characteristic"
expression <- rbind(characteristic, expression)
expression <- as.data.frame(t(expression))
for (i in 2:63111) {
  expression[,i] <- as.numeric(expression[,i])
}

# Plots ########################################################################

# Lowest padj: 6.830165e-12
ggplot(data = expression, aes(x = characteristic, y = ENSG00000184825)) +
  geom_violin() +
  geom_boxplot(width = 0.2, fill = "lavender") +
  scale_x_discrete(labels = c("ATXN2 intermediate repeat expansions", "Healthy controls")) +
  labs(x = "Disease status", y = "Raw counts")

# Heatmap of 10 lowest padj
lowest_padj <- gene_stats[!is.na(gene_stats$padj), ]
lowest_padj <- lowest_padj[order(lowest_padj$padj), ]
lowest_padj <- lowest_padj[1:10, ]
lowest_padj <- row.names(lowest_padj)

expression_lowest_padj <- expression[, colnames(expression) %in% lowest_padj]
expression_mat <- as.matrix(expression_lowest_padj)
correlation_mat <- cor(expression_mat)

gradient <- colorRampPalette(brewer.pal(9, "Blues"))
positive <- gradient(50)
negative <- rev(gradient(50))
heatmap.2(correlation_mat, trace = "none", col = c(negative, positive), margins = c(8, 8), cexRow = 0.8, cexCol = 0.8)

# Most correlated genes
diag(correlation_mat) <- NA
max_correlation <- max(correlation_mat, na.rm = TRUE)

lm <- lm(ENSG00000256018 ~ ENSG00000124635, expression)
plot(expression$ENSG00000124635, expression$ENSG00000256018, pch = 19, xlab = "ENSG00000124635", ylab = "ENSG00000256018")
abline(lm, col= "red", lwd = 2)
plot(residuals(lm), pch = 19, ylab = "Residual")
abline(h = 0, col = "red", lwd = 2)

wilcox_p <- wilcox.test(expression$ENSG00000256018, expression$ENSG00000124635)[[3]]

# PCA of 10 lowest padj
PCA <- prcomp(expression_mat, scale = TRUE)[[5]]
colors <- as.factor(expression$characteristic)
plot(PCA[,1], PCA[,2], pch = 19, col = colors, xlab = "PC1", ylab = "PC2")
#legend("topright", legend = levels(colors), fill = unique(colors), title = "Disease Status")

HC_PC1 <- PCA[expression$characteristic == "Healthy control",1]
ATXN2_PC1 <- PCA[expression$characteristic == "genotype: ATXN2 intermediate repeat expansions",1]
wilcox_p <- wilcox.test(HC_PC1, ATXN2_PC1)[[3]]
