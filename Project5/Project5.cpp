/*
 * Copy the contents of header.txt (filled out) and paste here
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way.
 * Please NOTE, you are responsible for ensuring that the functions work correctly in
 * your project solution. Just because the function works correctly in my solution does
 * NOT mean that the function will work correctly in yours.
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that
 * the amount of storage available in the elements[] array is equal to length
 */
bool binarySearch(int arr[], int l, int r, int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;
        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return true;
        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, r, x);
    }
    // We reach here when element is not
    // present in array
    return false;
}

/* done for you already */
void destroySet(Set* self) {
    free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
    self->len = 0;
    self->elements = nullptr;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
    self->elements = (int*) malloc(sizeof(int));
    self->elements[0] = x;
    self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
    self->elements = (int*) malloc(other->len * sizeof(int));
    for (int k = 0; k < other->len; k += 1) {
        self->elements[k] = other->elements[k];
    }
    self->len = other->len;
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
    if (self == other) { return; }
    destroySet(self);
    createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
    // O log(n)
    // quickSort(self->elements, 0, self->len-1);
    // binary search
    return binarySearch(self->elements, 0, self->len-1, x);
}

/*
 * add x as a new member to this set.
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
    int before;
    int current;
    for(int i = 0; i < self->len; i++){
        current = self->elements[i];
        if(current == x){
            return;
        }
        if(i == 0){
            if(current > x){
                // add x as a new member
                self->elements = (int*) realloc(self->elements, sizeof(int)*self->len+1);
                for(int j = self->len-1; j >= 0; j --){
                    self->elements[j+1] = self->elements[j];
                }
                self->elements[0] = x;
                self->len++;
                return;
            }
        } else if(i == self->len-1){
            if(current < x){
                self->elements = (int*) realloc(self->elements, sizeof(int)*self->len+1);
                self->elements[self->len] = x;
                self->len++;
                return;
            }
        }
        else{
            before = self->elements[i-1];
            if(x>before && x<current){
                //insert in between
            }
        }
    }
}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
    for(int i = 0; i< self->len; i++){
        if(self->elements[i]==x){
            //remove and realloc
            // 1. shift every value to the right of the element to the left
            for(int j = i; i < self->len -1 ; j++){
                self->elements[i] = self->elements[j];
            }
            self->len--;
            return;
        }
        return;
    }
}

/* done for you already */
void displaySet(const Set* self) {
    int k;

    printf("{");

    if (self->len == 0) {
        printf("}");
    }
    else {
        for (k = 0; k < self->len; k += 1) {
            if (k < self->len - 1) {
                printf("%d,", self->elements[k]);
            } else {
                printf("%d}", self->elements[k]);
            }
        }
    }
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    if( self->len ==0 && other-> len == 0){
        return true;
    } else if( self-> len != other ->len ){
        return false;
    } else{
        for(int i = 0; i < self->len; i++){
            if(self->elements != other->elements){
                return false;
            }
        }
        return true;
    }
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other)
{
    if (isEmptySet(self)){ //if self is empty then it will always be subset
        return true;
    }
    if (self->len > other->len){ //if self len is bigger then can't be a subset
        return false;
    }
    int j=0;
    for(int i=0; i<self->len; i++){
        if(j>=other->len){
            return false;
        }
        if(self->elements[i]==other->elements[j]){
            j++;
        }
        else if(self->elements[i] < other->elements[j]){ //if the jth element of other is bigger than self then every element of self isn't an element of other
            return false;
        } else{ //in this case only increment the j index and keep i index the same
            j++;
            i--;
        }
    }
    return true;
}

/* done for you */
bool isEmptySet(const Set* self) {
    return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
}

/* remove all elements from self that are also elements of other */
// void removeSet(Set* self, int x) {
void subtractFromSet(Set* self, const Set* other) {
    //void createCopySet(Set* self, const Set* other) {
    Set* subSet = (Set*) malloc(sizeof(Set));
    createEmptySet(subSet);
    int k = 0;
    int j = 0;
    int i = 0;
    while(i < self->len){
        if(self->elements[i]==subSet->elements[j]){
            if(subSet->elements == nullptr){
                subSet->len++;
                subSet-> elements = (int*) malloc (sizeof(int));
                subSet->elements[k] = self->elements[i];
                k++;
            } else{
                subSet->len++;
                subSet->elements = (int*) realloc(subSet->elements, subSet->len);
                subSet->elements[k] = self->elements[i];
                k++;
            }
            j++;
        } else if(self->elements[i] > subSet->elements[j]){
            i++;
        }else{
                j++;
                i--;
        }
    }
    createCopySet(self, subSet);
    destroySet(subSet);
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
}
