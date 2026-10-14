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
#SBATCH -o bank_CS.%N.%j.out

# Set the name of the error file
#SBATCH -e bank_CS.%N.%j.err

#------------------------------------------
#              OPENMP SPECIFIC
#------------------------------------------

# Prints date
date

# Compiling the Program
gcc -fopenmp -std=gnu99 bank_CS.c -o bank_CS -lm

# Prints starting new job
echo "Starting new job"

# Executes the compiled program
./bank_CS

# Prints finished job
echo "Finished job"

# Prints date
date
#------------------------------------------

