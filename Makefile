test:
	nvcc -I/usr/local/cuda/samples/common/inc -lcublas -o test main.cpp cuMatrix.cpp MemoryMonitor.cpp Linear.cu RNN.cu RNN_Cell.cu CTCBeamSearch.cu

