#!/bin/bash

#------------------------------------
#     SLURM SPECIFIC COMMANDS
#------------------------------------
# Gives a name for the job
#SBATCH --job-name=bank

# Ask the scheduler for Y CPU cores on the same compute node
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=3

# Set the name of the output file
#SBATCH -o bank.%N.%j.out

# Set the name of the error file
#SBATCH -e bank.%N.%j.err

#------------------------------------------
#              OPENMP SPECIFIC
#------------------------------------------

# Prints date
date

# Compiling the Program
gcc -fopenmp -std=gnu99 bank.c -o bank -lm

# Prints starting new job
echo "Starting new job"

# Executes the compiled program
./bank

# Prints finished job
echo "Finished job"

# Prints date
date
#------------------------------------------

