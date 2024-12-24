# PI值并行计算实验

使用不同的并行计算方法（MPI、Pthread、OpenMP）计算PI值的实验项目。

## 项目描述

本项目实现了四种不同的方法来计算PI值：
- 串行版本
- MPI分布式计算版本
- Pthread多线程版本
- OpenMP并行计算版本


## 功能特点

- 支持不同规模的计算（N=1000到1000000）
- 包含性能对比测试
- 自动生成性能对比图
- 完整的编译和运行脚本

## 环境要求

- GCC编译器
- OpenMPI
- Python3
- matplotlib
- numpy

## 安装依赖

```bash
sudo dnf install -y gcc openmpi openmpi-devel python3-numpy python3-matplotlib

# 设置MPI环境变量
export PATH=$PATH:/usr/lib64/openmpi/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib64/openmpi/lib
```

## 编译

```bash
make clean
make all
```

## 运行

```bash
# 串行版本
./build/serial_pi

# Pthread版本
./build/pthread_pi

# OpenMP版本
./build/openmp_pi

# MPI版本（4进程）
mpirun --map-by :OVERSUBSCRIBE -np 4 ./build/mpi_pi

# 生成性能对比图
cd scripts
python3 plot_performance.py
```

## 项目结构

```
pi_calculation/
├── src/                # 源代码
│   ├── serial_pi.c     # 串行版本
│   ├── mpi_pi.c        # MPI版本
│   ├── pthread_pi.c    # Pthread版本
│   └── openmp_pi.c     # OpenMP版本
├── scripts/            # 脚本
│   └── plot_performance.py  # 性能对比图脚本
├── build/             # 编译输出
├── results/           # 结果输出
└── Makefile          # 编译脚本
```

## 实验结果

性能对比图将保存在 `results/performance_comparison.png`
