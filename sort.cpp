#include <vector>
#include <iostream>
#include <random>
#include <time.h>
#include <iterator>

using namespace std;

#define INPUT vector<int>({3,45,623423,3242,324235,1231124,213124,2131,312314,5436,65645,3467,34235});

class sort
{
public:
    //1.选择排序
    void SelectSort(vector<int> &input){
        for (int i = 0; i < input.size() - 1; i++){
            for (int j = i + 1; j < input.size(); j++){
                if (input[i] > input[j])
                    swap(input[i], input[j]);
            }
        }
    }
    //2.冒泡排序
    void BubbleSort(vector<int> &input){
        for (int i = input.size() - 1; i > 0; i--)
            for (int j = 0; j < i; j++){
                if (input[j] > input[j + 1])
                    swap(input[j], input[j + 1]);
            }
    }
    //3.插入排序-shell排序调用版
    void InsertSort(vector<int> &input, int begin, int step){
        for (int i = begin + step; i < input.size(); i += step){
            for (int j = i - step; j >= 0; j -= step){
                if (input[j] > input[j + step]){
                    swap(input[j], input[j + step]);
                }
                else{
                    break;
                }
            }
        }
    }
    //4.shell排序
    void ShellSort(vector<int> &input){
        for (int step = input.size() / 2; step > 0; step = step / 2)
            for (int begin = 0; begin < step; begin++)
                InsertSort(input, begin, step);
    }
    //5.堆排序
    void HeapSort(vector<int> &input){
        //构造堆
        for (int i = (input.size() - 2) / 2; i >= 0; i--)
            PercolateDown(input, i, input.size());
        //进行排序
        for (int length = input.size(); length > 1; length--){
            swap(input[0], input[length - 1]);
            PercolateDown(input, 0, length - 1);
        }
    }
    //6.归并排序
    void MergeSort(vector<int> &input){
        vector<int> temp = input;
        merge(input, temp, 0, input.size());
    }
    //7.快速排序
    void QuickSort(vector<int> &input){
        srand(static_cast<unsigned int>(time(NULL)));
        partition(input, 0, input.size());
    }
//其他相关函数
    //打印函数
    void printVec(vector<int> &input){
        copy(input.begin(), input.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
private:
    //交换函数
    void swap(int &a ,int &b){
        int temp = b;
        b = a;
        a = temp;
    }
    //堆的下滤函数
    void PercolateDown(vector<int> &input, int index, int length){
        int left_index =  2 * index + 1;
        int right_index = 2 * index + 2;
        int max_index = index;
        if (left_index < length)
            if (input[left_index] > input[max_index])
                max_index = left_index;
        if (right_index < length)
            if (input[right_index] > input[max_index])
                max_index = right_index;
        if (index != max_index){
            swap(input[index], input[max_index]);
            PercolateDown(input, max_index, length);
        }
    }
    //归并函数
    void merge(vector<int> &input, vector<int> & temp, int begin, int end){
        if (begin > end - 2)
            return;
        int median = (begin + end) / 2;
        merge(input, temp, begin ,median);
        merge(input, temp, median, end);
        int left_index = begin;
        int right_index = median;
        for (int i = begin; i < end; i++){
            if (left_index == median)
                temp[i] = input[right_index++];
            else if (right_index == end)
                temp[i] = input[left_index++];
            else
                temp[i] = input[left_index] > input[right_index] ?
                    input[right_index++] : input[left_index++];
        }
        for (int i = begin; i < end; i++)
            input[i] = temp[i];
    }
    //快速排序函数
    void partition(vector<int> &input, int begin, int end){
        if (end - begin < 2)
            return;
        if (end - begin == 2){
            if (input[begin] > input[begin + 1])
                swap(input[begin], input[begin + 1]);
            return;
        }
        int random_index = begin + rand() % (end - begin);
        swap(input[random_index], input[end - 1]);
        int left_index = begin;
        int right_index = end - 2;
        while (left_index <= right_index){
            while (left_index <= right_index && input[left_index] <= input[end - 1])
                left_index++;
            while (left_index <= right_index && input[right_index] >= input[end - 1])
                right_index--;
            if (left_index > right_index)
                break;
            else
                swap(input[left_index++], input[right_index--]);
        }
        swap(input[left_index], input[end - 1]);
        partition(input, begin ,left_index);
        partition(input, left_index + 1, end);
    }
};

int main(){
    sort sort_obj;
    //测试选择排序
    vector<int> input = INPUT;
    sort_obj.SelectSort(input);
    sort_obj.printVec(input);
    //测试冒泡排序
    input = INPUT;
    sort_obj.BubbleSort(input);
    sort_obj.printVec(input);
    //测试插入排序
    input = INPUT;
    sort_obj.InsertSort(input, 0, 1);
    sort_obj.printVec(input);
    //测试shell排序
    input = INPUT;
    sort_obj.ShellSort(input);
    sort_obj.printVec(input);
    //测试堆排序
    input = INPUT;
    sort_obj.HeapSort(input);
    sort_obj.printVec(input);
    //测试归并排序
    input = INPUT;
    sort_obj.MergeSort(input);
    sort_obj.printVec(input);
    //测试快速排序
    input = INPUT;
    sort_obj.QuickSort(input);
    sort_obj.printVec(input);
    return 0;
}


