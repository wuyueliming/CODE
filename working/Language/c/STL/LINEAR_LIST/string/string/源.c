#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#if 0
void get_next(char* arr, int* next,int len) {//arr[0]里面存的就是数组的长度，这里还是作为变量传进来
	int i = 0;//当前字符下标
	int k = -1;//前缀的后一个字符的下标
	next[0] = -1;
	while (i < len-1) {
		if (k == -1 || arr[i] == arr[k]) {
			next[++i] = ++k;
		}
		else {
			k = next[k];
		}
	}

}
void get_nextval(char* arr, int* next, int len) {//arr[0]里面存的就是数组的长度，这里还是作为变量传进来
	int i = 0;//当前字符下标
	int k = -1;//前缀的后一个字符的下标
	next[0] = -1;
	while (i < len - 1) {
		if (k == -1 || arr[i] == arr[k]) {
			i++;
			k++;
			if (arr[i] == arr[k]) {
				next[i] = next[k];
			}
			else if (arr[i] != arr[k]) {
				next[i] = k;
			}
		}
		else {
			k = next[k];
		}
	}

}

int kmp(char* object, char* pattern, int pos) {//从第pos个字符开始往后找子串
	int index = -1;
	int obj_len = strlen(object);
	int ptn_len = strlen(pattern);
	int* next = (int*)malloc(sizeof(int) * ptn_len);
	get_next(pattern, next,ptn_len);
	
	for (int i = 0; i < ptn_len; i++) {
		printf("%d ", next[i]);
	}
	printf("\n");
	
	int i = pos;
	int j = 0;
	while (i < obj_len && j < ptn_len) {
		if (j==-1 || object[i] == pattern[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}
	free(next);
	
	if (j >= ptn_len) {
		index = i- ptn_len;
	}
	return index;
}

int main()
{
	char* object = "aaaabcabdabc";
	char* pattern = "aaaab";
	int index = kmp(object, pattern, 0);
	if ( index!= -1) {
		printf("子串在主串的第%d个位置",index);
		
	}
	else {
		printf("NULL");
	}


	return 0;
}
#endif



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                                    //第二天复习





#if 1
void get_next(char* str, int* next, int len) {
    int i = 0;
    int k = -1;
    next[0] = -1;
    while (i < len - 1) {
        if (k == -1 || str[i] == str[k]) {
            next[++i] = ++k;
        }
        else {
            k = next[k];
        }
    }

}

void get_nextval(char* str, int* next, int len) {
	int i = 0;
	int k = -1;//指向前缀的下一个字符，同时也表示前缀的长度
	next[0] = -1;
	while (i < len - 1) {
		if (k == -1 || str[i] == str[k]) {//现在指向的模式串字符已经不能和主串指向的字符匹配上了，
			++i;                    //那么如果跳到next[j]的那一个字符是和现在模式串指向的字符一样的，那么一定也不可能和主串现在指向的字符匹配上
			++k;                    //因为就是匹配不上了才会使用next来回溯，既然回溯后的字符和现在的字符一样那么肯定也不能匹配上，还是要继续回溯，
			if (str[i] == str[k]) {// 所以有了nextval数组，将模式串现在的next指向的字符的next作为现在的字符的next
				next[i] = next[k];
			}
			else {
				next[i] = k;
			}
		}
		else {
			k = next[k];
		}
	}

}


int kmp(char* txt, char* ptn) {
    int index = -1;
    int txt_len = strlen(txt);
    int ptn_len = strlen(ptn);
    int* next = (int*)malloc(sizeof(int) * ptn_len);
    get_nextval(ptn, next, ptn_len);

    for (int i = 0; i < ptn_len; i++) {
        printf("%d ", next[i]);
    }
    int i = 0;
    int j = 0;
    while (i < txt_len && j < ptn_len) {
        if (txt[i] == ptn[j] || j == -1) {
            i++;
            j++;
        }
        else {
            j = next[j];
        }
    }
    if (j >= ptn_len) {
        index = i - ptn_len;
    }
    free(next);
    return index;
}



int main()
{
    char* text = "helloworld";
    char* pattern = "aaaab";
    int index = kmp(text, pattern);
    if (index == -1) {
        printf("没找到");
    }
    else {
        printf("找到了，起始位置在%d号", index);
    }

    return 0;
}
#endif


























































































































































