#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
//int main()
//{
//	int n1 = 0;
//	scanf("%d", &n1);
//	int a = n1 / 100;
//
//	int b1 = n1 % 100;
//	int b2 = b1 / 10;
//
//	int c1 = n1 % 100;
//	int c2 = c1 % 10;             <<<<<<第二周作业
//
//
//	int theshy = c2 * 100 + b2 * 10 + a;
//
//
//		//printf("%d %d %d", c2, b2, a);
//		printf("%d",theshy );
//
//	return 0;
//}


//int main()
//{
//	int hour1, minute1;
//	int hour2, minute2;
//	printf("请分别输入时间1的小时和分钟:");
//	scanf("%d %d", &hour1, &minute1);
//	printf("请分别输入时间2的小时和分钟:");
//    scanf("%d %d", &hour2, &minute2);
//
//	int h = hour2 - hour1;
//	int m = minute2 - minute1;
//
//	if (h < 0)
//	{
//		h = -h;
//		m = -m;
//	};
//
//	if (m < 0)                      <<<<自己做的，算时间差的绝对值
//	{
//		h--;
//		m = m + 60;
//	};
//
//	printf("时差为%d小时%d分钟", h, m);
//
//	return 0;
//}

//int main()
//{
//	int BJT = 0;
//	int UTC = 0;
//	printf("请输入BJT北京时间:", BJT);
//	scanf("%d", &BJT);
//	UTC = BJT - 800;
//                                     <<<<<<<<第三周作业一
//	if (UTC < 0) {
//		UTC += 2400;
//	}
//	printf("UTC时间为%d", UTC);
//
//	return 0;
//}


//int main()
//{
//	int n = 0;
//	int t = 1;
//	double m = 0;
//	printf("请输入班级人数：");
//	scanf("%d", &n);
//
//	for (t = 1; t <= n; t++) {          <<<<<第三周作业二
//		m = t / 2;
//		if (m< t / 2.0) {       这里用除以2后的数（整数）是否和除以2.0算出来的数（浮点数）相等来判断单数、双数。
//			printf("%d\n", t);  也可以通过除余后等于0还是1来判断
//
//		}
//	}
//
//	return 0;
//}

//
//int main()
//{
//	int ji = 0;
//	int ou = 0;
//	int number = 0;
//	double judge = 0;
//	printf("请输入一系列正整数:");
//	do {
//		scanf("%d", &number);
//		judge = number / 2.0;
//		//printf("%d %d", judge, number / 2);      第四周作业一
//		if (number / 2 == judge) {
//			ou++;
//		}
//		else if (number != -1) { ji++; }
//	} while (number != -1);
//
//	printf("你输入了%d个奇数，%d个偶数", ji, ou);
//	return 0;
//}

//int main()
//{
//	int n = 0;//第n位
//	int x = 0;//第n位对应的数
//	int number = 0;
//	int sum = 0;
//	int a = 0;//将二进制转化为十进制
//	int exchange = 1;//2的n次幂
//	double judge1 = 0;
//	double judge2 = 0;
//	printf("请输入一个数字:");
//	scanf("%d", &number);
//	while (number > 0) {
//		n++;
//		x = number % 10;
//		number /= 10;
//		judge1 = n / 2.0;
//		judge2 = x / 2.0;
//		if ((n / 2 != judge1) && (x / 2 != judge2)) {                          //第四周作业二
//			//printf("1");
//			a = 1;
//		}else if ((n / 2 ==judge1 ) && (x / 2 == judge2)) {
//			//printf("1");
//			a = 1;
//		}else { 
//			a = 0;
//			//printf("0");
//		}
//		sum += a * exchange;
//		exchange *= 2;
//
//	}
//
//	printf("%d", sum);
//
//	return 0;
//}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//int main()
//{
//	int number = 0;
//	int n = 0;
//	int m = 0;
//	scanf("%d %d", &n, &m);
//	int i = 0;
//	int sum = 0;
//	int t = 0;
//	
//			while (t <= m)
//			{
//				for(i=2;i<=number;i++)
//				{ 
//					if (i == number) { 
//						sum += number;
//						t++; 
//						number++;
//						i = 2;
//					}
//					
//					
//					
//					if (number / i == 0) {
//						number++;
//						i = 2;
//					}
//					
//
//				}
//			}
//
//	
//	printf("%d", sum);
//
//
//	return 0;
//}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>第五周作业一，上面是想的第一个，下面是第二个
//int main()
//{
//	int n = 0;
//	int m = 0;
//	scanf("%d %d", &n, &m);
//	int t = 0;
//	int number = 2;
//	int sum = 0;
//	while (t < m) {
//		for (int x = 2; x < number; x++) {
//			if (number % x == 0) {
//				number++;
//				x = 1;
//				continue;
//			}
//		}
//		
//
//
//		t++;
//		printf("%d\n", number);
//		if (t >= n) {
//			sum += number;
//		}
//	
//		number++;
//	}
//	printf("%d", sum);
//
//	return 0;
//}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//int main()
//{
//	int number = 0;
//	scanf("%d", &number);
//	if (number < 0) { 
//		printf("fu ");
//		number = -number;
//	}
//
//	int t = 0;
//	t = number;
//	int mask = 1;
//	while (t >=10) {
//		mask *= 10;
//		t /= 10;
//	}
//	//printf("%d", mask);
//	int judge = 0;
//	while (number > 0) {
//		judge = number / mask;
//		number %= mask;
//		
//		switch (judge) {                    第五周作业二
//		case 1:
//			printf("yi");
//			break;
//		case 2:
//			printf("er");
//			break;
//		case 3:
//			printf("san");
//			break;
//		case 4:
//			printf("si");
//			break;
//		case 5:
//			printf("wu");
//			break;
//		case 6:
//			printf("liu");
//			break;
//		case 7:
//			printf("qi");
//			break;
//		case 8:
//			printf("ba");
//			break;
//		case 9:
//			printf("jiu");
//			break;
//		case 0:
//			printf("ling");
//			break;
//		}
//		if (mask >= 10) { printf(" "); }
//		mask /= 10;
//
//	}
//
//
//	return 0;
//}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//int main()
//{
//	int a = 0;
//	int b = 0;
//	scanf("%d/%d", &a, &b);//注意输入a和b时要严格遵守双引号里的格式
//	int cnt = 0;
//	printf("0.");                        //第六周作业
//	int x = 0;                      
//	int y = 0;
//	//printf("%d %d", a, b);
//	while (cnt <= 200) {
//		y = 10 * a / b;
//		printf("%d", y);
//		a = 10 * a % b;
//		cnt++;
//	}
//
//	return 0;
//}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<             以下尝试用数组、函数来做这个作业

//int main()
//{
//	int number[200];
//	int i = 0;
//	int cnt = 0;
//	int a = 0;
//	int b = 0;
//	scanf("%d/%d", &a, &b);
//	for (i = 0; i < 200; i++) {
//		number[i] = i;
//	}
//	printf("0.");
//	for (cnt = 0; cnt < 200; cnt++) {
//		number[cnt] = 10 * a / b;
//		a = 10 * a % b;
//		printf("%d", number[cnt]);
//
//	}
//	return 0;
//}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//int main()
//{
//	int a[101] = { 0 };
//	int b[101] = { 0 };
//	int sum[101] = { 0 };
//	int n = 1;
//	int A = 0;//第一个多项式的系数
//	int B = 0;//第二个多项式的系数
//	while (n != 0)
//	{
//		scanf("%d %d", &n, &A);           第七周作业一
//		a[n] = A;
//
//	}
//	/*for (int i = 0; i < 101; i++) {
//		printf("a[%d]=%d\n", i, a[i]);
//
//	}*/
//	n = 1;
//	while (n != 0)
//	{
//		scanf("%d %d", &n, &B);
//		b[n] = B;
//
//	}
//	sum[0] = a[0] + b[0];
//	for (int i = 100; i >=0; i--) {
//		if (a[i] + b[i]!=0) {
//			sum[i] = a[i] + b[i];
//			printf("%dx%d", sum[i], i);
//			if (sum[0] != 0&&i!=0 ) { printf("+"); }
//		}
//
//	}
//	
//
//	return 0;
//}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//int main()
//{
//    int arr[101][101] = { 0 };
//    int n = 0;
//    scanf("%d", &n);
//    for (int i = 0; i < n; i++)
//    {
//        int j = 0;
//        for (j = 0; j < n; j++)
//        {
//            scanf("%d", &arr[i][j]);
//        }
//    }
//    int themin;
//    int themax;
//    for (int i = 0; i < n; i++)
//    {
//        int j = 0;
//        themin = arr[0][0];
//        themax = arr[0][0];
//        for (j = 0; j < n; j++)
//        {
//            if (arr[i][j] < themin) { themin = arr[i][j]; }
//            if (arr[i][j] > themax) { themax = arr[i][j]; }
//        }
//    }
//
//
//
//
//    int max[101] = { 0 };
//    int min[101] = { 0 };
//
//    for (int i = 0; i < n; i++)
//    {
//        int j = 0;
//        int MAX = themin;
//        for (j = 0; j < n; j++)
//        {
//            if (arr[i][j] > MAX) {
//                MAX = arr[i][j];
//            }
//        }
//        max[i] = MAX;
//    }
//
//
//    for (int j = 0; j < n; j++)
//    {
//        int i = 0;
//        int MIN = themax;
//        for (i = 0; i < n; i++)
//        {
//            if (arr[i][j] < MIN) {
//                MIN = arr[i][j];
//            }
//        }
//        min[j] = MIN;
//    }
//
//
//
//
//
//    /*for (int i = 0; i < n; i++)
//    {
//        int j = 0;
//        for (j = 0; j < n; j++)
//        {
//            printf("第%d行第%d列=%d\n", i, j, arr[i][j]);      看看矩阵
//        }
//    }*/
//
//    /*for (int i = 0; i < n; i++)
//    {
//        printf("第%d行的max=%d\n",i,max[i]);      看看最大值
//    }
//
//
//    for (int j = 0; j < n; j++)
//    {
//        printf("第%d列的min=%d\n",j, min[j]);   看看最小值                 第七周作业二
//    }*/
//
//
//    int judge = 1;
//    for (int i = 0; i < n; i++)
//    {
//        int j = 0;
//        for (j = 0; j < n; j++)
//        {
//            if (arr[i][j] == max[i] && arr[i][j] == min[j]) {
//                printf("%d %d", i, j);
//                judge = 0;
//            }
//            
//        }
//
//    }
//    if (judge) { printf("No"); }
//    
//    return 0;
//}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//int main() {
//    char s[100];
//    int n;
// 
//     do{
//        scanf("%s", s);
//        n = strlen(s);
//        if (strstr(s, ".")) {//单词包含 . 则单词长度减1
//            n--;
//            printf("%d", n); //                          第八周作业一（网上抄的）
//        }
//        else {
//            printf("%d ", n);
//        }
//    } while (strstr(s, ".") == NULL);//单词不包含 . 则继续读入
//    printf("\n");
//   
//    return 0;
//}

/*首先，定义了一个字符数组 s，用于存储输入的单词。还定义了一个整数变量 n，用于存储单词的长度。

然后，使用 do - while 循环来读取单词并计算长度。循环的条件是单词中不包含句号（"."）。

在循环体内部，使用 scanf 函数读取一个单词，并使用 strlen 函数计算该单词的长度，并将结果存储到变量 n 中。

接下来，使用 strstr 函数判断单词中是否包含句号。如果包含句号，则将单词长度减1，因为题目要求结尾的句号不能计算在最后一个单词的长度内。

最后，根据单词是否包含句号，使用 printf 函数输出单词的长度。如果单词包含句号，则只输出长度，不输出空格。如果单词不包含句号，则输出长度后再输出一个空格。

循环结束后，使用 printf 函数输出一个换行符，表示输出结束。

注意：这个字符串的读取是可以先让用户输入很多单词，让程序以空格等为分界线通过do-while循环实现多次读取*/


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<？
/*              $GPRMC,024813.640,A,3158.4608,N,11848.3737,E,10.05,324.27,150706,,,A*50
   0、在很多GPS语句中选出GPRMC语句                                  筛选

   1、判断是否为GPRMC语句
   2、找到第一个A/V,判断该语句是否有效
   3、计算该条语句的校验值与结尾给出的校验值是否相等                判断
   4、得出该语句是否满足输出条件
   5、在所有满足条件的GPRMC语句中找到最后一条

   6、将这一条语句的UTC时间转化为北京时间并输出                     转换

*/
//int main()
//{
//    char arr[100] ;
//    scanf("%s", arr);          //这里需要一个循环输入，知道遇到END才停下
//    int num = 0;//异或值
//    int delta = strchr(arr, '*') - strchr(arr, '$') - 2;
//    
//    //printf("%d", arr[1] ^ arr[2]);
//    
//    if (strstr(arr, "$GPRMC") != NULL) {//判断是否为$GPRMC语句
//        if (strstr(arr, "V") == NULL) {//判断是否为有效信息
//            num = arr[1] ^ arr[2];                       //这里的1和2都是在$符号后面的第一个和第二个，如果不只输入一条语句则
//            for (int i = 2;i<1+delta ;i++ ) {   
//                for (int n = 1;i+n<=i+delta; n++) {          //计算异或值(这里不知道为什么，非要跳过逗号计算异或值）
//                    if (arr[i + n] != ',') {
//                        num = num ^ arr[i + n];
//                        break;
//                    }
//                    else {
//                        continue;
//                    } 
//                }
//                                                        第八周作业二第一次（半成品)
//            }
//        } 
//
//    }
// 
//    int judge = num % 65536;                                   
//    printf("%d", judge);
//
//    return 0;
//}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//int judge(char* arr,int len);
//int main()
//{
//    char arr[666] = { 0 };//循环输入时存储语句
//    char THEreserve[250] = { 0 };//符合输出条件的所有语句
//    char THEfinal[100] = { 0 };//最后一个符合条件的语句
//    while (strstr(arr,"END")==0)
//    {
//        scanf("%s", arr);
//        int len = strlen(arr);
//        if (strstr(arr, "$GPRMC") != 0) {
//            if (strchr(arr, 'V') == 0) {
//                if (judge(arr,len)) {
//                    strcat(THEreserve, arr);//将所有符合输出要求的语句保存起来
//                }
//            }
//        }
//
//
//    }
//    int t = 0;
//    int distence= strrchr(THEreserve, '$')- strchr(THEreserve, '$');//注意这里THEreserve[distence]就是最后的那个'$'
//    int len_of_final = strlen(THEreserve) - distence ;
//    for (int i = distence; i < strlen(THEreserve); i++) {
//        
//        THEfinal[t] = THEreserve[i];
//        t++;
//    }
//
//    printf("%s\n", THEreserve);//这个函数只认题目那个语句，修改一个数字就不行.想了一下，修改后的数据可能根本就不满足筛选的条件。。。。。。
//    printf("%s\n", THEfinal);
//    /*int hour = (THEfinal[7] - '0') * 10 + (THEfinal[8] - '0');
//    if (hour + 8 >= 24) {
//        hour = hour + 8 - 24;
//    }
//    else {
//        hour += 8;
//    }
//    printf("%d:%c%c:%c%c", hour, THEfinal[9], THEfinal[10], THEfinal[11], THEfinal[12]);
//     */
//
//    return 0;
//}
//
//int judge(char* arr,int len) {//验证校验和是否正确
//    int ret = 0;
//    int sum = arr[1];
//    int distence = strchr(arr, '*') - strchr(arr, '$');//arr[distence]正好是‘*’所在的位置
//    int number = len - distence;//十六进制的校验值的位数
//    for (int i = 2; i < distence; i++) {
//        sum = sum ^ arr[i];
//    }
//    int JUDGE_10 = sum % 65536;
//    //printf("%d", JUDGE_10);
//    
//    int JUDGE_16 = 0;
//    int exchange = 1;
//    for (int i = len-1; i > distence; i--) {//第一次调试，这里十六进制转换为十进制错了
//        JUDGE_16 += (arr[i]-'0') * exchange;
//        exchange *= 16;
//    }
//    
//    
//    if (JUDGE_10 == JUDGE_16) {
//        ret = 1;
//    }
//    
//    return ret;
//}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                                                       //进阶第一周作业
//int countzero(const char* a);//弄半天只能找第一个位置，根本不用这么多代码，几行就搞定了。现在这四不像真是无语了
//int search(char* b,char*a);
//int main()
//{
//    int NoAdd = -1;
//    char targetcha[10000] = { 0 };
//    char allcha[10000] = { 0 };
//    scanf("%s", targetcha);
//    scanf("%s", allcha);//输入的字符串输不了"空格，做个没空格版本好了。。。。。。。。。。。。。。。。
//    char* target = &targetcha;
//    char* all = &allcha;
//    
//    if (search(allcha, targetcha) == 0) {
//        printf("%d", NoAdd);
//    }
//    
//    int addadd = 0;
//    int add = 0;
//    while (search(all, target) != 0)
//    {
//        add = search(all, target);
//        //printf("%d", add);
//        all = strstr(all, targetcha) + strlen(targetcha);
//        
//        addadd += add;
//
//        printf("%d ", addadd);
//        addadd += 2;
//    }
//
//    
//    
//    return 0;
//}
//
//int search(char* b,char*a) {
//    int ret = 0;
// 
//    if (strstr(b, a) != NULL) {
//        ret = strstr(b, a) - b + 1;
//        
//    }
//   
//    return ret;
//}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//int main()
//{
//    char a[100] = { "abc" };
//    char b[100] = { "01abc5678abc" };
//    char* p = strstr(b, a);
//    *p = '\0';//这里是把p指的后面的钱都变成\0了
//    //p = strstr(p + 1, a);//在b中找第二个a的方法
//    
//    printf("%s", b);
//
//    return 0;
//}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//int main()
//{
//    char b[100];
//    scanf("%s", b);
//
//    printf("%s", b);//输入的字符串中含有空格就会终止
//
//    return 0;
//}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<我的半成品数零函数
//int countzero(const char *a) {//数空格函数，第一版不做好吧，反正字符串输入不了空格
//    int ret=-1;
//   
//    if ((a = strchr(a, ' ')) != NULL) {
//        ret = 1;
//    }
//    while (a != NULL); {
//        ret++;
//        //a = strchr(a+1, ' ');
//    }
//
//    return ret;
//}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<取找到的子字符串前面的字符串
//
// char* p = strstr(b, a);
//char contain = *p;
//*p = '\0';
//char* zero = (char*)malloc(strlen(b) + 1);
//zero = strcpy(zero, b);
// 
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                                                        //进阶第四周作业

//typedef struct _NODE {
//    struct _NODE* last;
//    int num;
//    struct _NODE* next;
//} NODE;
//
//typedef struct _LIST {
//    NODE* head;
//    NODE* tail;
//} LIST;
//
//void add(LIST* Plist, int number);
//void SHOW(LIST* Plist);
//void release(LIST* Plist);
//void antidromicSHOW(LIST* Plist);
//int main()
//{
//    //做一个双向链表(add,release,search
//    LIST list;
//    list.head = NULL;
//    list.tail = NULL;
//    //正向输入数字，读到-1就停止
//    int number = 0;
//    while (number != -1) {
//        scanf("%d", &number);
//        if (number != -1) {
//            add(&list, number);
//        }
//    }
//    //逆向输出链表
//    //SHOW(&list);
//    antidromicSHOW(&list);
//    //释放空间
//    release(&list);
//
//    return 0;
//}
//
//void add(LIST* Plist, int number) {
//    NODE* p = (NODE*)malloc(sizeof(NODE));
//    p->num = number;
//    p->next = NULL;
//    NODE* final = Plist->head;
//
//    if (final) {
//        while (final->next) {
//            final = final->next;
//        }
//        final->next = p;
//    }
//    else {
//        Plist->head = p;
//    }
//
//    p->last = final;
//    Plist->tail = p;
//}
//void release(LIST* Plist) {
//    NODE* q = Plist->head;
//    for (NODE* p = q->next; p; q = p, p = p->next) {
//        free(q);
//    }
//    free(q);
//}
//
//void SHOW(LIST* Plist) {
//    NODE* p;
//    for (p = Plist->head; p; p = p->next) {
//        printf("%d ", p->num);
//    }
//}
//
//void antidromicSHOW(LIST* Plist) {
//    NODE* p;
//
//    for (p = Plist->tail; p; p = p->last) {
//        printf("%d ", p->num);
//    }
//
//}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                                            //1、混乱数组排序，二分查找
                                                            //2、可变数组
                                                            //3、双向链表
                                                            //4、指针 + 数组，重新理解
                                                            //5、进阶一、四周作业
                                                            //6、素数判断（进阶）:素数的倍数，2的倍数，到根号
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//int isPirme(int x)//一定不要在函数内定义函数！！！！！！！！！！！！！！！！！
//{
//	int ret = 1;
//	int i;
//	if (x == 1) {
//		ret = 0;
//	}
//	else if (x != 2 && x % 2 == 0)//<<<<<<<<偶数一定不是素数，所以排除掉除2外的偶数，可以将循环次数减少一半
//	{
//		ret = 0;
//	}
//	for (i = 3; i < sqrt(x); i += 2)//<<<<<根据数学知识，i只要循环到x的平方根就能判断是否为素数
//	{
//		if (x % i == 0) {
//			ret = 0;
//			break;
//		}
//	}
//	return ret;
//}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//
//int main()
//{
//	int isPrime[100];     这段代码中的100是说100以内的素数（翁恺的数组大小可以用常变量定义，我不行）
//		int i;
//	int x;
//	for (i = 0; i < 100; i++) {
//		构造n以内的素数表
//			isPrime[i] = 1;                         1、定义一个prime[n]，把所有元素初始化为1，prime[x]为1代表是一个素数
//	}                                           2、令x = 2
//		for (x = 2; x < 100; x++) {
//			3、如果x是素数，则对于（i = 2；i * x < n; i++），令prime[i * x] = 0；
//				if (isPrime[x]) {
//					4、令x++，如果x < n, 重复3，否则结束
//						for (i = 2; i * x < 100; i++) {
//							isPrime[i * x] = 0;
//						}
//				}
//		}
//		for (i = 2; i < 100; i++) {
//			if (isPrime[i]) {
//				printf("%d\t", i);
//			}
//		}
//
//		printf("\n");
//
//		return 0;
//}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//int judge(int);
//int main()
//{
//    int max = 0;
//    scanf("%d", &max);
//    int amax = max + 1;
//    int* a = (int*)malloc(sizeof(int) * amax);
//    for (int i = 0; i < amax; i++) {
//        a[i] = 1;
//    }
//
//    for (int i = 0; i < amax; i++) {
//        if (judge(i)) {
//            if(i!=1)for (int n = 2; n * i <= amax; n++) {//靠了，1的倍数把所有数字全都标记成非素数了
//                a[i*n] = 0;
//            }
//        }
//        else {
//            a[i] = 0;
//        }
//    }
//
//    for (int i = 0; i < amax; i++) {
//        if (a[i]==1) {
//            printf("%d\n", i);
//        }
//    }
//
//    return 0;
//}
//
//int judge(int a) {
//    int ret = 1;
//    if (a == 2) {
//        ret = 1;
//    }
//    else if(a%2==0){
//        ret = 0;
//    }
//    else {
//        for (int i = 2; i < sqrt(a); i++) {
//            if (a % i == 0) {
//                ret = 0;
//            }
//        }
//    }
//    
//
//    return ret;
//}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//int main()
//{
//	//将一个混乱的数组按大小排序
//	int number = 0;
//	scanf("%d", &number);
//	int a[] = { 22,3,14,34,59,31,4,5,13,26,55 };
//	int max = 0;
//	int len = sizeof(a) / sizeof(a[0]);
//	for (int i = len - 1; i >= 1; i--)
//	{
//		max = 0;
//		for (int x = 0; x < i + 1; x++) {
//			if (a[x] > a[max]) {
//				max = x;
//			}
//		}
//		int change = a[max];
//		a[max] = a[i];
//		a[i] = change;
//	}
//
//	for (int t = 0; t < len; t++) {
//		printf("%d ", a[t]);
//	}
//	printf("\n");
//	//利用二分法来提高搜索的效率
//
//	int left = 0;
//	int right = len - 1;
//	while (right >= left)
//	{
//		int mid = (left + right) / 2;
//		if (a[mid] == number) {
//			printf("在数组a的第%d位", mid);
//			break;
//		}
//		else if (a[mid] > number) {
//			right = mid - 1;
//		}
//		else {
//			left = mid + 1;
//		}
//
//	}
//
//	return 0;
//}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int main()
{
    int a[] = { 0,2,33,23,45,5,24,21,17,19 };
    int max = a[0];
    int contain = 0;//又做了一遍混乱数组排序，contain存下标，max存最大值。我是真的蠢，直接让max做下标，a[max]来做最大值就好了，反正又可以不用a[max]做运算
    int len ;
    for (len = sizeof(a) / sizeof(a[0]); len >= 1; len--) {
        for (int i = 0; i < len; i++) {
            if (a[i] > max) {
                max = a[i];
                contain = i;
            }
        }
        a[contain] = a[len - 1];
        a[len - 1] = max;
        max = a[0];
        contain = 0;
    }

    /*for (int i = 0; i < 10; i++) {
        printf("%d\n", a[i]);
    }*/
    len = 10;
    int num = 0;
    scanf("%d", &num);


    int left = 0;
    int right = len - 1;
    int mid = (left + right) / 2;
    while (right>=left) {
        if (num > a[mid]) {
            left = mid + 1;
            mid = (left + right) / 2;
        }
        else if (num < a[mid]) {
            right = mid - 1;
            mid = (left + right) / 2;
        }
        else {
            printf("%d", mid);
            right=mid-1;//竟然忘了还有break了，还有continue，服了
        }
        
    }
    


    return 0;
}













