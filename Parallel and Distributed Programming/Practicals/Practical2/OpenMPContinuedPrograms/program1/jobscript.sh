#!/bin/bash

#------------------------------------
#     SLURM SPECIFIC COMMANDS
#------------------------------------
# Gives a name for the job
#SBATCH --job-name=interleave

# Ask the scheduler for Y CPU cores on the same compute node
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=2

# Set the name of the output file
#SBATCH -o interleave.%N.%j.out

# Set the name of the error file
#SBATCH -e interleave.%N.%j.err

#------------------------------------------
#              OPENMP SPECIFIC
#------------------------------------------

# Prints date
date

# Compiling the Program
gcc -fopenmp -std=gnu99 interleave.c -o interleave -lm

# Prints starting new job
echo "Starting new job"

# Executes the compiled program
./interleave

# Prints finished job
echo "Finished job"

# Prints date
date
#------------------------------------------

