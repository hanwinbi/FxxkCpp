#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

void BubbleSort(vector<int> &vec);
void QuickSort(vector<int> &vec, int low, int high);
int Partition(vector<int> &vec, int low, int high);
void print(const vector<int> vec);
void SelectSort(vector<int> &vec);
int M_max(const vector<int> vec, int start);
void HeapSort(vector<int> &vec);
void max_heapify(vector<int> &vec, int i, int end);
void swap(vector<int> &vec, int i, int j);
void MergeSort(vector<int> &vec, vector<int> &temp, int low, int mid, int high);
void MergePartition(vector<int> &vec, vector<int> &temp, int low, int high);
void ShellSort(vector<int> &vec);
void CountSort(vector<int>& nums);
int maxbit(vector<int> nums);
void RadixSort(vector<int>& nums);

// 冒泡排序，从小到大排序
void BubbleSort(vector<int> &vec){
    int len = vec.size();
    for(int i = len; i >= 0; --i){
        for(int j = 1; j < i; ++j){
            if(vec[j-1] > vec[j]){  // > 改为 < 就是从大到小排序 
                int temp = vec[j-1];
                vec[j-1] = vec[j];
                vec[j] = temp;
            }
        }
    }
}

// 快速排序
void QuickSort(vector<int> &vec, int low, int high){
    if(low >= high){
        return ;
    }
    int Pivot = Partition(vec, low, high);
    QuickSort(vec, low, Pivot-1);
    QuickSort(vec, Pivot+1, high);
}

int Partition(vector<int> &vec, int low, int high){
    int i=rand()%(high-low+1)+low;  //随机选取主元
    swap(vec[low],vec[i]);
    int pivot = vec[low];
    while(low<high){
        while(low < high && vec[high] >= pivot) --high;
        vec[low] = vec[high];
        while(low < high && vec[low] <= pivot) ++low;
        vec[high] = vec[low];
    }
    vec[low] = pivot;
    return low;
}

// 简单选择排序
void SelectSort(vector<int> &vec){
    for(int i = 0; i != vec.size(); ++i){
        int max = M_max(vec, i);
        int temp = vec[max];
        vec[max] = vec[i];
        vec[i] = temp;
    }
}

int M_max(const vector<int> vec, int start){
    int max = INT_MIN;
    int pos = start;
    for(int i = start; i < vec.size(); ++i){
        if(vec[i] > max){
            max = vec[i];
            pos = i;
        }
    }
    return pos;
}

// 直接插入排序
void InsertSort(vector<int> &vec){
    int len = vec.size();
    for (int i = 1; i < len; i++)
    {
        int value = vec[i];
        int pos = i;
        while(pos > 0 && vec[pos-1] > value){
            vec[pos] = vec[pos - 1];
            pos--;
        }
        vec[pos] = value;
    }
}

// 堆排序
void swap(vector<int> &vec, int i, int j){
    int temp = vec[i];
    vec[i] = vec[j];
    vec[j] = temp;
}

void max_heapify(vector<int> &vec, int i, int end){
    int parent = i; // 数组中的位置
    int son = 2*i + 1;  // 用左子节点表示子孙
    while(son <= end){
        if(son+1 <= end && vec[son] < vec[son+1]){ //找到左右子节点中最大的那一个
            son++;
        }
        if(vec[son] > vec[parent]){    // 将大元素作为parents
            swap(vec, son, parent);
            parent = son;
            son = 2*parent + 1;
        }else{
            break;
        }
    }
}

void HeapSort(vector<int> &vec){
    int len = vec.size();
    for (int i = len/2-1; i >= 0; --i)
    {   
        max_heapify(vec, i, len-1);
    }
    for(int i = len - 1; i >= 0; --i){
        swap(vec, 0, i);
        max_heapify(vec, 0, i-1);
    }
}

// 归并排序
// 分治的思想
void MergePartition(vector<int> &vec, vector<int> &temp, int low, int high){
    if(low < high){
        int mid = (low + high)/2;
        MergePartition(vec, temp, low, mid);    //左数组
        MergePartition(vec, temp, mid+1, high); //右数组
        MergeSort(vec, temp, low, mid, high);   // 合并两个子序列
    }
}

void MergeSort(vector<int> &vec, vector<int> &temp, int low, int mid, int high){
    int i = low;
    int j = mid+1;
    int k = 0;
    while(i <= mid && j <= high){
        temp[k++] = vec[i] > vec[j] ? vec[i++] : vec[j++];
    }
    while(i <= mid){
        temp[k++] = vec[i++];
    }
    while (j <= high)
    {
        temp[k++] = vec[j++];
    }
    for(int i = 0; i < k; ++i){
        vec[low+i] = temp[i];
    }
}

//希尔排序
// 递减增量，k_1, k_2 ... k_i,(k_t > k_i), k_i = 1
// 将数组分成K个小块，小块内部进行插入排序
void ShellSort(vector<int> &vec){
    int len = vec.size();
    for(int delta = len/2; delta >= 1; delta /= 2){
        for(int i = delta; i < len; ++i){
            for(int j = i; j >= delta && vec[j] > vec[j-delta]; j -= delta){
                int temp = vec[j];
                vec[j] = vec[j-delta];
                vec[j-delta] = temp;
            }
        }
    }
}
// O(n^{3/2})
void KuthShellSort(vector<int> &vec){
    int delta = 1;
    while(delta < vec.size()/3){
        delta = delta * 3 + 1;
    }
    for(; delta >= 1; delta /= 3){
        for(int i = delta; i < vec.size(); ++i){
            for(int j = i; j >= delta && vec[j] > vec[j-delta]; j -= delta){
                int temp = vec[j];
                vec[j] = vec[j-delta];
                vec[j-delta] = temp;
            }
        }
    }
}

// 计数排序
void CountSort(vector<int>& nums){
    //找最小 最大值 确定数组大小
    int max = INT_MIN;
    int min = INT_MAX;
    for(int i = 0; i != nums.size(); ++i){
        if(nums[i] > max) max = nums[i];
        if(nums[i] < min) min = nums[i];
    }

    int k = max - min + 1;
    vector<int> count(k, 0);
    vector<int> res;

    for(int i = 0; i < nums.size(); ++i){
        count[nums[i] - min]++;
    }

    int pos = 0;
    for(int i = 0; i < k; ++i){
        while(count[i]>0){
            nums[pos++] = i + min;
            count[i]--;
        }
    }
}

//基数排序
int maxbit(vector<int> nums){
    int max = INT_MIN;
    int min = INT_MAX;
    for(int i = 0; i != nums.size(); ++i){
        if(nums[i] > max) max = nums[i];
        if(nums[i] < min) min = nums[i];
    }

    max = max>(-min) ? max:(-min);
    int count = 1;
    while(max>= 10){
        max /= 10;
        count++;
    }
    return count;
}

void RadixSort(vector<int>& nums){
    // 最大数的数位是多少
    int bit = maxbit(nums);
    vector<int> count(19, 0);
    // 循环数位
    vector<vector<int>> res(19);
    int pos, cur;
    for(int i = 0, mod = 1; i < bit; ++i, mod *= 10){
        for(int i = 0; i != nums.size(); ++i){
            pos = (nums[i]/mod) % 10;
            res[pos+9].push_back(nums[i]);
        }
        cur = 0;

        for(int i = 0; i < 19; ++i){
            for(int j = 0; j < res[i].size(); ++j){
                nums[cur++] = res[i][j];
            }
            res[i].clear();
        }
    }
}

//打印输出
void print(const vector<int> vec){
    for(int i = 0; i != vec.size(); ++i){
        cout << vec[i] << endl;
    }
}

int main(){
    vector<int> vec = {5,7,9,6,3,4,1};
    // BubbleSort(vec);
    // QuickSort(vec, 0 ,vec.size()-1);
    // SelectSort(vec);
    // InsertSort(vec);
    // HeapSort(vec);
    // vector<int> temp = vec;
    // MergePartition(vec, temp, 0, vec.size()-1);
    // ShellSort(vec);
    // KuthShellSort(vec);
    // CountSort(vec);
    RadixSort(vec);
    print(vec);
}