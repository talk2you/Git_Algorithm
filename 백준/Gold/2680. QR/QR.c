#include <stdio.h>
#include <string.h>

enum md { md_num = 1, md_alpha = 2, md_bit_8 = 4, md_kanji = 8, md_termi = 0 };
char strList[45] = { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ $%*+-./:" };

char qr[50];
char bin_code[300];
char ans[300];
int ans_size;

void init()
{
	memset(ans, 0, sizeof(char) * 300);
	memset(bin_code, 0, sizeof(char) * 300);
	ans_size = 0;
}

void input()
{
	scanf("%s", qr);
}

// 2진수로 변환
void decode_toBin()
{
	char bin[5] = { 0, };
	int temp, j = 3, i = 0;;
	
	while (qr[i])
	{
		memset(bin, '0', sizeof(char) * 4);
		
		if (qr[i] - '0' < 10)
			temp = qr[i] - '0';
		else
			temp = qr[i] - 'A' + 10;

		j = 3;

		while (temp)
		{
			bin[j--] = temp % 2 + '0';
			temp /= 2;
		}
		strcat(bin_code, bin);
		++i;
	}
}

// 슬라이싱하고 숫자로 리턴
int slicing_code(int cnt)
{
	char data[20] = { 0, };
	int temp = 0;

	strncpy(data, bin_code, cnt);
	strcpy(&bin_code[0], &bin_code[cnt]);

	int i = 0;
	while (data[i])
	{
		temp <<= 1;
		temp |= (data[i] % 2);
		++i;
	}

	return temp;
}

// 모드값 가져오기
int get_mode()
{
	return slicing_code(4);
}

// 카운트값 가져오기
int get_count(int mode)
{
	if (mode == md_num)	// Numeric
		return slicing_code(10);
	else if (mode == md_alpha)	// Alphanumeric
		return slicing_code(9);
	else if (mode == md_bit_8)	// 8bit Byte
		return slicing_code(8);
	else if (mode == md_kanji)	// Kanji
		return slicing_code(8);
	else	// Termination
		return -1;
}


void Numeric(int count)
{
	int num;
	char buf[5];
	while (count)
	{
		if (count >= 3)
		{
			count -= 3;
			ans_size += 3;
			num = slicing_code(10);
			sprintf(buf, "%03d", num);
			strcat(ans, buf);			
		}
		else if (count == 2)
		{
			count -= 2;
			ans_size += 2;
			num = slicing_code(7);
			sprintf(buf, "%02d", num);
			strcat(ans, buf);
		}
		else
		{
			count -= 1;
			ans_size += 1;
			num = slicing_code(4);
			sprintf(buf, "%1d", num);
			strcat(ans, buf);
		}
	}
}

void Alphanumeric(int count)
{
	int num;
	char buf[5];
	while (count)
	{
		if (count >= 2)
		{
			count -= 2;
			ans_size += 2;
			num = slicing_code(11);
			sprintf(buf, "%c%c", strList[num / 45], strList[num % 45]);
			strcat(ans, buf);
		}
		else
		{
			count -= 1;
			ans_size++;
			num = slicing_code(6);
			sprintf(buf, "%c", strList[num]);
			strcat(ans, buf);
		}		
	}
}

void Bit_8(int count)
{
	int num;
	char buf[5];
	while (count)
	{
		count -= 1;
		ans_size++;
		num = slicing_code(8);
		if (0x20 <= num && num <= 0x7E)
		{
			if (num == '\\')
			{
				sprintf(buf, "\\");
				strcat(ans, buf);
			}
			else if (num == '#')
			{
				sprintf(buf, "\\#");
				strcat(ans, buf);
			}
			else
			{
				sprintf(buf, "%c", num);
				strcat(ans, buf);
			}
		}
		else
		{
			
			sprintf(buf, "\\%02X", num);
			strcat(ans, buf);
		}
	}
}

void Kanji(int count)
{
	int num;
	char buf[10];
	while (count)
	{
		count -= 1;
		ans_size += 1;
		num = slicing_code(13);
		sprintf(buf, "#%04X", num);
		strcat(ans, buf);
	}
}

void solve()
{
	int mode, count;

	decode_toBin();

	while (1)
	{
		mode = get_mode();
		count = get_count(mode);

		if (mode == md_num)
			Numeric(count);
		else if (mode == md_alpha)
			Alphanumeric(count);
		else if (mode == md_bit_8)
			Bit_8(count);
		else if (mode == md_kanji)
			Kanji(count);
		else
			break;
		
	}
	printf("%d %s\n",ans_size, ans);
}

int main(void)
{
	int T;
	scanf("%d", &T);
	for (int t = 1;t <= T;t++)
	{
		init();
		input();
		solve();
	}
}