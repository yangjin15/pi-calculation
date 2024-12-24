import matplotlib.pyplot as plt
import numpy as np
import subprocess
import re
import os

def run_program(program, n_processes=None):
    results = []
    if program == 'mpi_pi':
        cmd = ['mpirun', '--map-by', ':OVERSUBSCRIBE', '-np', str(n_processes), f'../build/{program}']
    else:
        cmd = [f'../build/{program}']
    
    try:
        output = subprocess.check_output(cmd).decode()
        
        for line in output.split('\n'):
            if line and not line.startswith('N') and not line.startswith('Serial') and not line.startswith('MPI') and not line.startswith('Pthread') and not line.startswith('OpenMP'):
                try:
                    n, pi, time = line.split()
                    results.append((int(n), float(time)))
                except:
                    continue
    except Exception as e:
        print(f"Error running {program}: {e}")
    
    return results

def main():
    programs = {
        'Serial': 'serial_pi',
        'MPI (4 processes)': 'mpi_pi',
        'Pthread (4 threads)': 'pthread_pi',
        'OpenMP (4 threads)': 'openmp_pi'
    }
    
    plt.figure(figsize=(10, 6))
    
    markers = ['o-', 's-', '^-', 'D-']
    colors = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728']
    
    for (label, program), marker, color in zip(programs.items(), markers, colors):
        try:
            if program == 'mpi_pi':
                results = run_program(program, n_processes=4)
            else:
                results = run_program(program)
            
            if results:
                n_values = [r[0] for r in results]
                times = [r[1] for r in results]
                plt.plot(np.log10(n_values), times, marker, label=label, color=color, 
                        linewidth=1.5, markersize=6)
        except Exception as e:
            print(f"Error running {program}: {e}")
    
    plt.xlabel('Iteration Count (log10(N))')
    plt.ylabel('Time (seconds)')
    plt.title('Performance Comparison of Different PI Calculation Methods')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    
    # 确保results目录存在
    os.makedirs('../results', exist_ok=True)
    plt.savefig('../results/performance_comparison.png', dpi=300, bbox_inches='tight')
    plt.close()

if __name__ == '__main__':
    main() 