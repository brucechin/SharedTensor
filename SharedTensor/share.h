#pragma once

#include<iostream>
#include<vector>

using namespace std;

template<class T>
class Share {

private:
	int nDev=4;
	bool flag[8];
	T mean ;
	bool meanReady = false;
public:
    T data[8];
    Share(){
        memset(flag,false,sizeof(bool));
        
    }
	bool Push(T input,int index) {

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
            if(!flag[0]) return false;

			for (int i = 0; i < nDev; i++) {
				if (!flag[i]) return false;
				else data[0] += data[i];
			}
			mean = data[0] * 1.0f /  nDev;
			meanReady = true;
		}
		return true;
	}

	void ResetMean() {
		for (int i = 0; i < nDev; i++) {
			if (flag[i]) return;
		}
		meanReady = false;
	}

	T Pop(int index) {
		while(!MeanReady());//deadlock may occur 
       		flag[index] = false;
		T tmp = mean;
		ResetMean();
		return tmp;    
	}

};
