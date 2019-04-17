#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#pragma warning (disable:4996)

using namespace std;	// using 지시문
using std::cout;		// using 선언

class Product {
	char* name;
	int price;
public:
	Product() {}
	Product(const char* prodName, int prodPrice) {
		name = new char[strlen(prodName) + 1];
		strcpy(name, prodName);
		price = prodPrice;
	}
	~Product() {
		cout << "Product 객체 소멸" << endl;
		delete[] name;
	}
	void setName(const char* prodName) {
		name = new char[strlen(prodName) + 1];
		strcpy(name, prodName);
	}
	char* getName(void) {
		return name;
	}
	void setPrice(int prodPrice) {
		price = prodPrice;
	}
	int getPrice(void) {
		return price;
	}
};
class ProductContainer {
	const int maxProduct;	// 최대 상품 개수
	Product **product;	// 상품을 담는 더블포인터
	int topindex;	// 상품의 개수
public:
	ProductContainer(int num = 1) : maxProduct(num) {	// 생성자는 개수만큼 포인터를 할당
		product = new Product*[num];
		//for (int i = 0; i < num; i++)
		//	product[i] = new Product;
		topindex = 0;
	}
	~ProductContainer(){
		for (int i = 0; i < topindex; i++) {
			delete product[i];
		}
		delete[] product;
		cout << "ProductContainer 객체 소멸" << endl;
	}
	void addProduct(const char* name, int price)  {	// 입력
		//*product[topindex++] = Product(name, price);
		product[topindex++] = new Product(name, price);
	}
	void modProduct(const char* prevName,const char* name, int price) {
		for (int i = 0; i < topindex; i++) {
			if (strcmp(prevName, product[i]->getName())) {
				product[i]->setName(name);
				product[i]->setPrice(price);
			}
		}
	}
	void printProduct() {
		for (int i = 0; i < topindex; i++) {
			cout << "[" << i << "] 번" << endl;
			cout << "상품 : " << product[i]->getName() << endl;
			cout << "금액 : " << product[i]->getPrice() << endl;
		}
	}
	void printProduct(int index) {
		if (index >= topindex) {
			cout << "상품 번호 오류입니다." << endl;
			return;
		}

		cout << "[" << index << "] 번" << endl;
		cout << "상품 : " << product[index]->getName() << endl;
		cout << "금액 : " << product[index]->getPrice() << endl;
	}
};

int main()
{
	int productTotalNum, menuInput, inputPrice, prodIndex;
	char menuList[6][21] = { "메뉴 입력", "1)상품추가", "2)상품수정", "3)종합출력" "4)상품출력", "5)종료" };
	char inputProduct[20], prevInputProduct[20];

	cout << "상품 입력 개수를 입력하시오: ";
	cin >> productTotalNum;
	//ProductContainer productContainer(productTotalNum);
	ProductContainer *productContainer = new ProductContainer(productTotalNum);

	while (1) {
		cout << "***** 상품 추가/수정/출력 *****" << endl;
		for (int i = 0; i < 6; i++)
			printf("%s\n", menuList[i]);
		cout << "  >> ";
		cin >> menuInput;
		switch (menuInput) {
		case 1:	// 상품 추가
			cout << "상품명 : ";
			cin >> inputProduct;
			cout << "상품가 : ";
			cin >> inputPrice;
			
			productContainer->addProduct(inputProduct, inputPrice);

			cout << "상품 입력 완료" << endl;
			cout << --productTotalNum << "개의 추가 상품 입력이 가능합니다." << endl;
			break;			
		case 2:	// 상품 수정
			cout << "수정할 상품명 : ";
			cin >> prevInputProduct;
			cout << "상품명 : ";
			cin >> inputProduct;
			cout << "상품가 : ";
			cin >> inputPrice;
			productContainer->modProduct(prevInputProduct, inputProduct, inputPrice);
			break;	
		case 3:	// 종합 출력
			cout << "모든 상품 출력" << endl;
			productContainer->printProduct();
			break;	
		case 4:	// 개별 출력
			cout << "출력 상품 번호 : ";
			cin >> prodIndex;
			productContainer->printProduct(prodIndex);
			break;	
		case 5:	// 종료
			cout << "프로그램을 종료 합니다." << endl;
			delete productContainer;
			return 0;
			break;
		default:
			break;

		}
	}
}