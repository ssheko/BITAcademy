#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#pragma warning (disable:4996)

using namespace std;	// using ���ù�
using std::cout;		// using ����

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
		cout << "Product ��ü �Ҹ�" << endl;
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
	const int maxProduct;	// �ִ� ��ǰ ����
	Product **product;	// ��ǰ�� ��� ����������
	int topindex;	// ��ǰ�� ����
public:
	ProductContainer(int num = 1) : maxProduct(num) {	// �����ڴ� ������ŭ �����͸� �Ҵ�
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
		cout << "ProductContainer ��ü �Ҹ�" << endl;
	}
	void addProduct(const char* name, int price)  {	// �Է�
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
			cout << "[" << i << "] ��" << endl;
			cout << "��ǰ : " << product[i]->getName() << endl;
			cout << "�ݾ� : " << product[i]->getPrice() << endl;
		}
	}
	void printProduct(int index) {
		if (index >= topindex) {
			cout << "��ǰ ��ȣ �����Դϴ�." << endl;
			return;
		}

		cout << "[" << index << "] ��" << endl;
		cout << "��ǰ : " << product[index]->getName() << endl;
		cout << "�ݾ� : " << product[index]->getPrice() << endl;
	}
};

int main()
{
	int productTotalNum, menuInput, inputPrice, prodIndex;
	char menuList[6][21] = { "�޴� �Է�", "1)��ǰ�߰�", "2)��ǰ����", "3)�������" "4)��ǰ���", "5)����" };
	char inputProduct[20], prevInputProduct[20];

	cout << "��ǰ �Է� ������ �Է��Ͻÿ�: ";
	cin >> productTotalNum;
	//ProductContainer productContainer(productTotalNum);
	ProductContainer *productContainer = new ProductContainer(productTotalNum);

	while (1) {
		cout << "***** ��ǰ �߰�/����/��� *****" << endl;
		for (int i = 0; i < 6; i++)
			printf("%s\n", menuList[i]);
		cout << "  >> ";
		cin >> menuInput;
		switch (menuInput) {
		case 1:	// ��ǰ �߰�
			cout << "��ǰ�� : ";
			cin >> inputProduct;
			cout << "��ǰ�� : ";
			cin >> inputPrice;
			
			productContainer->addProduct(inputProduct, inputPrice);

			cout << "��ǰ �Է� �Ϸ�" << endl;
			cout << --productTotalNum << "���� �߰� ��ǰ �Է��� �����մϴ�." << endl;
			break;			
		case 2:	// ��ǰ ����
			cout << "������ ��ǰ�� : ";
			cin >> prevInputProduct;
			cout << "��ǰ�� : ";
			cin >> inputProduct;
			cout << "��ǰ�� : ";
			cin >> inputPrice;
			productContainer->modProduct(prevInputProduct, inputProduct, inputPrice);
			break;	
		case 3:	// ���� ���
			cout << "��� ��ǰ ���" << endl;
			productContainer->printProduct();
			break;	
		case 4:	// ���� ���
			cout << "��� ��ǰ ��ȣ : ";
			cin >> prodIndex;
			productContainer->printProduct(prodIndex);
			break;	
		case 5:	// ����
			cout << "���α׷��� ���� �մϴ�." << endl;
			delete productContainer;
			return 0;
			break;
		default:
			break;

		}
	}
}