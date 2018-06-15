#pragma once

#include<iostream>
#include<vector>

using namespace std;

class Tensor {

private:
	int nDev;
	vector<bool> flag = vector<bool>(100,false);
	vector<float> data = vector<float>(100, 0);
	float mean;
	bool meanReady = false;
public:

	bool Push(float input,int index) {

		if (flag[index] == false) {
			data[index] = input;
			flag[index] = true;
			return true;
		}
		else
			return false;
	}

	bool MeanReady() {
		if (!meanReady) {
			for (int i = 0; i < nDev; i++) {
				if (!flag[i]) return false;
				else mean += data[i];
			}
			mean /= nDev;
			meanReady = true;
		}
		return true;
	}

	void ResetMean() {
		for (int i = 0; i < nDev; i++) {
			if (flag[i]) return;
		}
		mean = 0;
		meanReady = false;
	}

	float Pop(int index) {//可以改为无返回类型，把mean赋给传入的指针对应的值
		if (MeanReady()) {
			flag[index] = false;
			float tmp = mean;
			ResetMean();
			return tmp;
		}
	}

};