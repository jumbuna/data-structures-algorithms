#pragma once

//linear logarithmic time complexity
//linear space complexity

template<class T>
void merge(T *array, size_t lsaStart, size_t lsaEnd, size_t rsaEnd) {	
	int ll = lsaEnd-lsaStart+1; //size of left subarray
	int rl = rsaEnd-lsaEnd; // size of right subarray
	
	T lsa[ll]; //left subarray
	T rsa[rl];//right subarray
	
	//filling subarray with there values
	for(int i = 0; i < ll; i++) {
		lsa[i] = array[lsaStart+i];
	}
	for(int i = 0; i < rl; i++) {
		rsa[i] = array[lsaEnd+i+1];
	}
	//b - subarray start index on array
	//l - left subarray index
	//r - right subarray index
	int b = lsaStart, l = 0, r = 0;
	while(l < ll && r < rl) {
		if(lsa[l] <= rsa[r]) {
			array[b] = lsa[l];
			++l;
		}else {
			array[b] = rsa[r];
			++r;
		}
		++b;
	}
	while(l < ll) {
		array[b] = lsa[l];
		++l;
		++b;
	}
	
	while(r < rl) {
		array[b] = rsa[r];
		++r;
		++b;
	}
}

template<class T>
void mergeSort(T *array, size_t start, size_t end) {
	if(start < end) {
		int midian = start+(end - start)/2;
		mergeSort(array, start, midian);
		mergeSort(array, midian+1, end);
		merge(array, start, midian, end);
	}
}