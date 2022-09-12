# create function for displaying stats
print_stats <- function(lst,name) {
  s <- sum(lst[,])
  md  <- median(lst[,])
  mn <- mean(lst[,])
  rg <- range(lst[,])
  cat("\nstats for", name)
  cat("\nsum =", s)
  cat("\nmedian =", md)
  cat("\nmean =", mn)
  cat("\nrange =", rg, "\n\n")
}

# create function for displaying covariance & correlation
print_cov_cor <- function(x,y) {
  corr <- cor(x[,],y[,])
  covar <- cov(x[,],y[,])
  cat("correlation =", corr)
  cat("\ncovariance =", covar)
}

# read in dataset from Boston.csv
data <- read.csv("Boston.csv")

# get the 'rm' column store as list
rm <- data["rm"]

# get the 'medv' column store as list
medv <- data["medv"]

# print stats for each
print_stats(rm,"rm")
print_stats(medv,"medv")

# print covariance and correlation for both
print_cov_cor(rm,medv)
