#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// --- Helper Utilities ---
void printArray(const vector<int>& arr) {
    if (arr.empty()) {
        cout << "Array is empty." << endl;
        return;
    }
    for (int num : arr) cout << num << " ";
    cout << endl;
}

// Q3: Core Two-Pointer In-Place Reversal Helper
void reverseArrayHelper(vector<int>& arr, int start, int end) {
    while (start < end) {
        swap(arr[start], arr[end]);
        start++;
        end--;
    }
}

// --- Individual Lab Components ---

// Q1 & Q2: Extrema Scanner
void findExtrema(const vector<int>& arr) {
    if (arr.size() < 2) {
        cout << "Error: Array must have at least 2 elements for second largest tracking." << endl;
        return;
    }
    int smallest = INT_MAX, largest = INT_MIN, secondLargest = INT_MIN;
    
    for (int num : arr) {
        if (num < smallest) smallest = num;
        
        if (num > largest) {
            secondLargest = largest;
            largest = num;
        } else if (num > secondLargest && num != largest) {
            secondLargest = num;
        }
    }
    cout << "Smallest: " << smallest << "\nLargest: " << largest << endl;
    if (secondLargest == INT_MIN) cout << "Second Largest: Does not exist" << endl;
    else cout << "Second Largest: " << secondLargest << endl;
}

// Q4 & Q5: In-Place Rotations
void rotateArray(vector<int>& arr, int k, bool left) {
    int n = arr.size();
    if (n == 0) return;
    k = k % n; // Defensive against k > n
    
    if (left) {
        reverseArrayHelper(arr, 0, k - 1);
        reverseArrayHelper(arr, k, n - 1);
        reverseArrayHelper(arr, 0, n - 1);
    } else {
        reverseArrayHelper(arr, 0, n - 1);
        reverseArrayHelper(arr, 0, k - 1);
        reverseArrayHelper(arr, k, n - 1);
    }
}

// Q6: Find Duplicates (Unsorted Array)
void findDuplicates(const vector<int>& arr) {
    vector<int> temp = arr;
    sort(temp.begin(), temp.end());
    cout << "Duplicate elements: ";
    bool found = false;
    for (size_t i = 1; i < temp.size(); i++) {
        if (temp[i] == temp[i - 1]) {
            if (i == 1 || temp[i] != temp[i - 2]) { // Print unique duplicates
                cout << temp[i] << " ";
                found = true;
            }
        }
    }
    if (!found) cout << "None";
    cout << endl;
}

// Q7: Remove Duplicates from a Sorted Array (Two-Pointer In-Place modification)
void removeDuplicatesSorted(vector<int>& arr) {
    if (arr.empty()) return;
    int uniqueIdx = 0; // Tracks position of last unique element found
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] != arr[uniqueIdx]) {
            uniqueIdx++;
            arr[uniqueIdx] = arr[i];
        }
    }
    arr.resize(uniqueIdx + 1); // Shrink to unique size
}

// Q8: Find Missing Number from 1 to N
int findMissingNumber(const vector<int>& arr, int N) {
    long long expectedSum = (long long)N * (N + 1) / 2;
    long long actualSum = 0;
    for (int num : arr) actualSum += num;
    return expectedSum - actualSum;
}

// Q9: Merge Two Sorted Arrays
vector<int> mergeSortedArrays(const vector<int>& arr1, const vector<int>& arr2) {
    vector<int> merged;
    size_t i = 0, j = 0;
    while (i < arr1.size() && j < arr2.size()) {
        if (arr1[i] <= arr2[j]) {
            merged.push_back(arr1[i++]);
        } else {
            merged.push_back(arr2[j++]);
        }
    }
    while (i < arr1.size()) merged.push_back(arr1[i++]);
    while (j < arr2.size()) merged.push_back(arr2[j++]);
    return merged;
}

// Q10: Find Pair with Given Sum (Two Sum - Two Pointer approach on sorted data)
void findTwoSum(vector<int> arr, int target) {
    sort(arr.begin(), arr.end()); // Squeezing requires sorted array
    int left = 0, right = arr.size() - 1;
    bool found = false;
    while (left < right) {
        int currentSum = arr[left] + arr[right];
        if (currentSum == target) {
            cout << "Pair found: (" << arr[left] << ", " << arr[right] << ")" << endl;
            found = true;
            left++; right--; // Keep looking for other pairs
        } else if (currentSum < target) {
            left++;
        } else {
            right--;
        }
    }
    if (!found) cout << "No pair exists with the given sum." << endl;
}

// --- Interactive Interface ---
int main() {
    vector<int> workingArray = {12, 3, 1, 3, 35, 1, 10, 34};
    int choice;

    do {
        cout << "\n===== THE ULTIMATE ARRAY SUITE =====" << endl;
        cout << "Current Array: "; printArray(workingArray);
        cout << "------------------------------------" << endl;
        cout << "1. Find Smallest, Largest & Second Largest (Q1, Q2)" << endl;
        cout << "2. Reverse Array In-Place (Q3)" << endl;
        cout << "3. Rotate Array (Left / Right) (Q4, Q5)" << endl;
        cout << "4. Find Duplicate Elements (Q6)" << endl;
        cout << "5. Remove Duplicates from Sorted Array (Q7)" << endl;
        cout << "6. Find Missing Number from 1 to N (Q8)" << endl;
        cout << "7. Merge Two Sorted Arrays (Q9)" << endl;
        cout << "8. Find Pair with Target Sum (Q10)" << endl;
        cout << "9. Reset Array to Default Data" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                findExtrema(workingArray);
                break;
            case 2:
                reverseArrayHelper(workingArray, 0, workingArray.size() - 1);
                cout << "Array Reversed!" << endl;
                break;
            case 3: {
                int k; bool left;
                cout << "Enter positions to rotate: "; cin >> k;
                cout << "Rotate Left? (1 for Yes, 0 for Right): "; cin >> left;
                rotateArray(workingArray, k, left);
                break;
            }
            case 4:
                findDuplicates(workingArray);
                break;
            case 5:
                sort(workingArray.begin(), workingArray.end());
                cout << "Sorting array first..." << endl;
                removeDuplicatesSorted(workingArray);
                break;
            case 6: {
                vector<int> missingArr = {1, 2, 4, 5, 6};
                cout << "Using custom sample [1, 2, 4, 5, 6], N = 6" << endl;
                cout << "Missing Number: " << findMissingNumber(missingArr, 6) << endl;
                break;
            }
            case 7: {
                vector<int> a1 = {1, 3, 5, 7}, a2 = {2, 4, 6, 8};
                cout << "Merging [1,3,5,7] and [2,4,6,8]..." << endl;
                vector<int> merged = mergeSortedArrays(a1, a2);
                cout << "Merged Array: "; printArray(merged);
                break;
            }
            case 8: {
                int target;
                cout << "Enter target sum: "; cin >> target;
                findTwoSum(workingArray, target);
                break;
            }
            case 9:
                workingArray = {12, 3, 1, 3, 35, 1, 10, 34};
                cout << "Array reset." << endl;
                break;
            case 0:
                cout << "Exiting Array Suite." << endl;
                break;
            default:
                cout << "Invalid Option!" << endl;
        }
    } while (choice != 0);

    return 0;
}