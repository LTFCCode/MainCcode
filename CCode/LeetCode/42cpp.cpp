#include "stdafx.h"

void test42(){
	vector<int> height({ 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1});
	int result = 0;
	for (int i = 0; i<height.size() - 2;){
		if (height[i] == 0){
			i++;
			continue;
		}
		for (int h = i + 1; h<height.size() ; h++){
			if (height[h] >= height[i]){
				for (int aim = i + 1; aim<h; aim++){
					result += height[i] - height[aim];
				}
				break;
			}
		}
		i++;
	}
}