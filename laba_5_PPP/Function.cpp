#include "Function.h"

double getFinalPrice(double price, double discount) {
	return (price * ((100 - discount) / 100));
}

//bool checkString(string s) {
//	int counter = 0;
//	for (int i = 0; i < s.length(); i++) { // ������ �� ��������
//		if ((s[i] >= '�' && s[i] <= '�' || s[i] >= '�' && s[i] <= '�') ||
//			(s[i] >= 'A' && s[i] <= 'Z' || s[i] >= 'a' && s[i] <= 'z')) {
//			counter += 1;
//		}
//	}
//	if (counter == s.length()) {
//		return 1;
//	}
//	else {
//		return 0;
//	}
//}