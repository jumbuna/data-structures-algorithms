#pragma once

template<class T>
void merge(T *array, size_t p, size_t q, size_t e) {
	//p-beginning index/left index
	//q-left index
	//e-end index
	
	int ll = q-p+1; //size of left subarray
	int rl = e-q; // size of right subarray
	
	T lsa[ll]; //left subarray
	T rsa[rl];//right subarray
	
	//filling subarray with there values
	for(int i = 0; i < ll; i++) {
		lsa[i] = array[p+i];
	}
	for(int i = 0; i < rl; i++) {
		rsa[i] = array[q+i+1];
	}
	
	int b = p, l = 0, r = 0;
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