#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // customer arrays
  struct customer {
    char name[20];
    int age;
    int code;
    int type;
  };
  struct customer allCustomers[200];

  // product arrays
  struct product {
    char name[20];
    int code;
    int price;
  };
  struct product allProducts[200];
  struct product purchasedProducts[200];
  struct product searchprod;

  // independant variables
  int i, j, k, menuInput, prodTotalCost, totProdNum, totCustNum, searchInput,
      customerCode, purchasedQuantity[200], purchasedCode[200],
      totProdPurchased, costPerProd[200], flag = 0, bill = 0, billGST;

  while (1) { // while(1) is true untill exit(0)
    printf("\n\n\n1. Add Customer\n");
    printf("2. Add Products\n");
    printf("3. Billing\n");
    printf("4. Discount calculation\n");
    printf("5. Search Products\n");
    printf("0. Exit Program\n");
    printf("\nWhat you want to do? : ");
    scanf("%d", &menuInput);
    printf("\n\n");

    // exitting program
    if (menuInput == 0) {
      exit(0);
    }

    // add customer
    else if (menuInput == 1) {
      printf("\nHow many customers you want to add?");
      scanf("%d", &totCustNum);
      for (i = 0; i < totCustNum; i++) {
        printf("\nAdding (%d)th customer", i + 1);
        printf("\nCustomer Type (1 -> Regular and 0-> Temporary) : ");
        scanf("%d", &allCustomers[i].type);
        printf("\nCustomer Name : ");
        scanf("%s", allCustomers[i].name);
        printf("\nCustomer Age : ");
        scanf("%d", &allCustomers[i].age);
        printf("\nCustomer Code : ");
        scanf("%d", &allCustomers[i].code);
      }
    }

    // add product
    else if (menuInput == 2) {
      // adding products to inventory
      printf("\nHow many products you want to add?");
      scanf("%d", &totProdNum);
      for (i = 0; i < totProdNum; i++) {
        printf("\n\nAdding (%d)th product", i + 1);
        printf("\nProduct Code : ");
        scanf("%d", &allProducts[i].code);
        printf("\nProduct Name : ");
        scanf("%s", allProducts[i].name);
        printf("\nProduct Price : ");
        scanf("%d", &allProducts[i].price);
      }
    }

    // calculate bill
    else if (menuInput == 3) {
      // reading products
      printf("\nEnter no of products purchased: ");
      scanf("%d", &totProdPurchased);
      for (i = 0; i < totProdPurchased; i++) {
        printf("\nEnter code of (%d)th product : ", i + 1);
        scanf("%d", &purchasedCode[i]);
        printf("\nHow much purchased? : ");
        scanf("%d", &purchasedQuantity[i]);
      }

      // copying purchased product list to a new array
      for (i = 0; i < totProdNum; i++) {
        // checking if product code exists
        for (k = 0; k < totProdPurchased; k++) {
          // creating a new array and storing product prices in it
          if (allProducts[i].code == purchasedCode[k]) {
            for (j = 0; j < totProdPurchased; j++) {
              purchasedProducts[j].price = allProducts[i].price;
              purchasedProducts[j].code = allProducts[i].code;
              strcpy(purchasedProducts[j].name, allProducts[i].name);
            }
          } else {
            printf("\n\nError in product code\n\n");
          }
          // finding total amount
          for (i = 0; i < totProdPurchased; i++) {
            prodTotalCost = purchasedProducts[i].price * purchasedQuantity[i];
            bill = bill + prodTotalCost;
          }

          // adding GST
          billGST = bill + ((0.05) * bill);

          // displaying recipt
          printf(" *****  FINAL BILL ***** \n");
          printf("--------------------------------------------------------\n");
          printf(
              "S.N.|    NAME     |   CODE   |  QUANTITY |  PRICE | TOTAL \n");
          printf("--------------------------------------------------------\n");
          for (i = 0; i < totProdNum; i++) {
            costPerProd[i] = purchasedQuantity[i] * purchasedProducts[i].price;

            printf(
                "%d     %s             %d          %d         %d       %d \n",
                i + 1, purchasedProducts[i].name, purchasedProducts[i].code,
                purchasedQuantity[i], purchasedProducts[i].price,
                costPerProd[i]);
          }
          printf(
              "\n--------------------------------------------------------\n");
          printf("\nTotal Cost excluding taxes : %d\n", bill);
          printf("\nAmount to be Paid with 5 percent GST : %d\n", billGST);
          printf("\n******** Thankyou, Visit Again ********\n\n\n\n");
        }

        // discount calculation
        else if (menuInput == 4) {
          // discount for regular customers
          printf("Enter customer code : ");
          scanf("%d", &customerCode);
          if (customerCode == 1) {
            billGST = (90 / 100) * billGST;
            printf("\nRegular customer bill is : %d\n", billGST);
          } else
            printf("\nNormal customer bill is : %d\n", billGST);

          // discount for bulk buying
          for (i = 0; i < totProdNum; i++) {
            if (purchasedQuantity[i] >= 10) {
              billGST = billGST - ((10 / 100) * billGST);
              printf("\nBulk order bill is : %d\n", billGST);
              break;
            }
          }

          // printing final bill
          printf("\n\n***** Total amount to be paid is : %d ******\n\n",
                 billGST);
        }

        // search product
        else if (menuInput == 5) {
          // getting input
          printf("Enter product code or product price : ");
          scanf("%d", &searchInput);
          printf("\n");

          // searching for product
          for (int i = 0; i < totProdNum; i++) {
            if (searchInput == allProducts[i].code ||
                searchInput == allProducts[i].price) {
              searchprod.price = allProducts[i].price;
              searchprod.code = allProducts[i].code;
              strcpy(searchprod.name, allProducts[i].name);
              flag = 1;
              break;
            } else {
              flag = 0;
            }
          }

          // displaying product details
          if (flag == 1) {
            printf("Product Found. Details :\n");
            printf("Product Code : %d\n", searchprod.code);
            printf("Product Name : %s\n", searchprod.name);
            printf("Product Price : %d\n", searchprod.price);
          } else {
            printf("\nProduct not found\n");
          }
        }

        // otherwise
        else {
          printf("\nPlease eneter correct code\n");
        }
      }
    }

  /* References
  https://stackoverflow.com/questions/32313150/array-type-char-is-not-assignable
  https://www.geeksforgeeks.org/exit0-vs-exit1-in-c-c-with-examples
  https://www.javatpoint.com/array-of-structures-in-c
  https://stackoverflow.com/questions/37538/how-do-i-determine-the-size-of-my-array-in-c
  https://www.programiz.com/c-programming/c-pointers-arrays
  https://data-flair.training/blogs/file-handling-in-c/
  https://www.javatpoint.com/remove-an-element-from-an-array-in-c
  https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/
  https://stackoverflow.com/questions/1898657/result-of-sizeof-on-array-of-structs-in-c
  https://www.scaler.com/topics/c/string-comparison-in-c/ */