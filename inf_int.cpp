#define _CRT_SECURE_NO_WARNINGS
#include "inf_int.h"

/*
Originally written by
��ǻ�Ͱ��к�
������
*/

inf_int::inf_int()
{
    this->digits = new char[2];   // �����Ҵ�

    this->digits[0] = '0';      // default �� 0 ����
    this->digits[1] = '\0';
    this->length = 1;
    this->thesign = true;
}

inf_int::inf_int(int n) {
    char buf[100];

    if (n < 0) {      // ���� ó��
        this->thesign = false;
        n = -n;
    }
    else {
        this->thesign = true;
    }

    int i = 0;
    while (n > 0) {         // ���ڸ� ���ڿ��� ��ȯ�ϴ� ����
        buf[i] = n % 10 + '0';

        n /= 10;
        i++;
    }

    if (i == 0) {   // ������ ������ 0�� ���
        new (this) inf_int();   // ������ ��ȣ��...gcc���� �����Ͽ����� �ִٰ� ��. inf_int()�� ��� ������ �ν��Ͻ��� ������. 
    }
    else {
        buf[i] = '\0';

        this->digits = new char[i + 1];
        this->length = i;
        strcpy(this->digits, buf);
    }
}

inf_int::inf_int(const char* str)
{
    // to be filled 
    // ��ȣ ó�� 
    // "100"�� ���Դٸ� ���� ǥ���� �°� "001"�� ��ȯ
    // ex) "-1053" -> thesign=false, digits="3501", len=4
       // Initialize default values
    this->length = 0;
    this->thesign = true;
    this->digits = nullptr;

    if (str == nullptr || str[0] == '\0') {
        
        new (this) inf_int(); 
        return;
    }

    int start_index = 0;

    
    if (str[0] == '-') {
        this->thesign = false;
        start_index = 1;
    }

    
    this->length = strlen(str) - start_index;

    if (this->length == 0) {
        
        new (this) inf_int(); 
        return;
    }

    
    this->digits = new char[this->length + 1];

    
    for (int i = 0; i < this->length; i++) {
        this->digits[i] = str[start_index + this->length - 1 - i];
    }

   
    this->digits[this->length] = '\0';

}

inf_int::inf_int(const inf_int& a) {
    this->digits = new char[a.length + 1];

    strcpy(this->digits, a.digits);
    this->length = a.length;
    this->thesign = a.thesign;
}

inf_int::~inf_int() {
    delete[] digits;      // �޸� �Ҵ� ����
}


inf_int& inf_int::operator=(const inf_int& a)
{
    if (this->digits) {
        delete this->digits;      // �̹� ���ڿ��� ���� ��� ����.
    }
    this->digits = new char[a.length + 1];

    strcpy(this->digits, a.digits);
    this->length = a.length;
    this->thesign = a.thesign;

    return *this;
}

bool operator==(const inf_int& a, const inf_int& b)
{
    
    if ((strcmp(a.digits, b.digits) == 0) && a.thesign == b.thesign)   // ��ȣ�� ����, ������ ��ġ�ؾ���.
        return true;
    return false;
}

bool operator!=(const inf_int& a, const inf_int& b)
{
    return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b)
{
    // to be filled
    // ���밪 ��
    // �� �� ����� ��� ���� ���� ���� �״�� return
    // �� �� ������ ��� ���� ���� ���� �����Ͽ� return
    // ��ȣ�� �ٸ� ���, a�� ����� ��� b�� ����, a�� ������ ��� b�� ����̱⿡ a�� ��ȣ�������� ��ȯ�ϸ� ��

     
    if (a.thesign && b.thesign) {
        if (a.length > b.length) {
            return true;
        }
        if (a.length < b.length) {
            return false;
        }
        for (int i = a.length - 1; i >= 0; i--) {
            if (a.digits[i] > b.digits[i]) {
                return true;
            }
            if (a.digits[i] < b.digits[i]) {
                return false;
            }
        }
        return false;
    }

   
    if (!a.thesign && !b.thesign) {
        return operator-(a) > operator-(b);
    }

    
    return a.thesign;
}

bool operator<(const inf_int& a, const inf_int& b)
{
    if (operator>(a, b) || operator==(a, b)) {
        return false;
    }
    else {
        return true;
    }
}

inf_int operator+(const inf_int& a, const inf_int& b)
{
    inf_int c;
    unsigned int i;

    if (a.thesign == b.thesign) {   // ������ ��ȣ�� ���� ��� + �����ڷ� ����
        for (i = 0; i < a.length; i++) {
            c.Add(a.digits[i], i + 1);
        }
        for (i = 0; i < b.length; i++) {
            c.Add(b.digits[i], i + 1);
        }

        c.thesign = a.thesign;

        return c;
    }
    else {   // ������ ��ȣ�� �ٸ� ��� - �����ڷ� ����
        if (a < b) {
            c = b - (-a);
            c.thesign = b.thesign;
        }
        else {
            c = a - (-b);
            c.thesign = a.thesign;
        }

        if (c.length == 1 && c.digits[0] == '0') {
            c.thesign = true; 
        }

        return c;
    }
}

inf_int operator-(const inf_int& a) {


    inf_int result = a;
    result.thesign = !a.thesign; 
    return result;

}

inf_int operator-(const inf_int& a, const inf_int& b)
{
   

    if (a == b) {
       
        return inf_int();
    }

    if (a.thesign && b.thesign) {  
        if (a < b) {
            inf_int result = b - a;
            result.thesign = false; 
            return result;
        }

        inf_int result = a;
        int carry = 0;

        for (int i = 0; i < b.length; i++) {
            int sub = (a.digits[i] - '0') - (b.digits[i] - '0') - carry;
            if (sub < 0) {
                sub += 10;
                carry = 1;
            }
            else {
                carry = 0;
            }

            result.digits[i] = sub + '0';
        }

        for (int i = b.length; i < a.length; i++) {
            int sub = (a.digits[i] - '0') - carry;
            if (sub < 0) {
                sub += 10;
                carry = 1;
            }
            else {
                carry = 0;
            }

            result.digits[i] = sub + '0';
        }

        
        while (result.length > 1 && result.digits[result.length - 1] == '0') {
            result.length--;
        }

        return result;
    }
    else if (!a.thesign && !b.thesign) {  
        
        return (-b) - (-a);
    }
    else if (a.thesign && !b.thesign) { 
        inf_int result = a + (-b);
        result.thesign = true;
        return result;
    }
    else { 
        return (-a) + b;
    }
}

inf_int operator*(const inf_int& a, const inf_int& b)
{
   

    if (a == inf_int(0) || b == inf_int(0)) {
        return inf_int(0);
    }

    int len1 = a.length;
    int len2 = b.length;
    int lenResult = len1 + len2;
    inf_int result;

    result.digits = new char[lenResult + 1];
    for (int i = 0; i < lenResult; i++) {
        result.digits[i] = '0';
    }
    result.digits[lenResult] = '\0';

    for (int i = 0; i < len1; i++) {
        int carry = 0;
        int num1 = a.digits[i] - '0';

        for (int j = 0; j < len2; j++) {
            int num2 = b.digits[j] - '0';
            int product = num1 * num2 + (result.digits[i + j] - '0') + carry;

            carry = product / 10;
            result.digits[i + j] = (product % 10) + '0';
        }

        //result.digits[i + len2] = carry + '0';
        int k = i + len2;
        while (carry > 0) {
            int sum = (result.digits[k] - '0') + carry;
            carry = sum / 10;
            result.digits[k] = (sum % 10) + '0';
            k++;
        }

    }

    
    while (lenResult > 1 && result.digits[lenResult - 1] == '0') {
        lenResult--;
    }

    result.length = lenResult;
    result.thesign = (a.thesign == b.thesign);  

    return result;
}


ostream& operator<<(ostream& out, const inf_int& a)
{
    int i;

    if (!a.thesign) {
        out << '-';
    }
    for (i = a.length - 1; i >= 0; i--) {
        out << a.digits[i];
    }
    return out;
}

istream& operator>>(istream& in, inf_int& a) {

    string input;
    in >> input;

    if (input.empty()) {
        a = inf_int();
        return in;
    }

    if (input[0] == '-') {
        a.thesign = false;
        input = input.substr(1);
    }
    else {
        a.thesign = true;
    }

    if (a.digits) {
        delete[] a.digits;
    }

    a.digits = new char[input.length() + 1];
    strcpy(a.digits, input.c_str());
    a.length = input.length();

    return in;

}

void inf_int::Add(const char num, const unsigned int index)   // a�� index �ڸ����� n�� ���Ѵ�. 0<=n<=9, ex) a�� 391�϶�, Add(a, 2, 2)�� ����� 411
{
    if (this->length < index) {
        this->digits = (char*)realloc(this->digits, index + 1);

        if (this->digits == NULL) {      // �Ҵ� ���� ����ó��
            cout << "Memory reallocation failed, the program will terminate." << endl;

            exit(0);
        }

        this->length = index;               // ���� ����
        this->digits[this->length] = '\0';   // �ι��� ����
    }

    if (this->digits[index - 1] < '0') {   // ���� ���� '0'���� ���� �ƽ�Ű���� ��� 0���� ä��. �������� �ʾҴ� ���ο� �ڸ����� ��� �߻�
        this->digits[index - 1] = '0';
    }

    this->digits[index - 1] += num - '0';   // �� ����


    if (this->digits[index - 1] > '9') {   // �ڸ��ø��� �߻��� ���
        this->digits[index - 1] -= 10;   // ���� �ڸ������� (�ƽ�Ű��) 10�� ����
        Add('1', index + 1);         // ���ڸ��� 1�� ���Ѵ�
    }
}