#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// functions
void discount(int disc, float billGST)
{
  if (disc == 1)
  {
    billGST = (0.9) * billGST;
    printf("\nRegular customer bill is : %f\n", billGST);
  }
  else
  {
    printf("\nNormal customer bill is : %f\n", billGST);
  }
}
void error() { printf("\nPlease enter correct code\n"); }

// product struct
struct product
{
  char name[20];
  int code;
  int price;
};

// customer struct
struct customer
{
  char name[20];
  int age;
  int code;
  int phone;
};
int main()
{

  struct customer allCustomers[200];
  struct product allProducts[200];
  struct product purchasedProducts[200];
  struct product searchprod;
  int prodTotalCost, totProdNum, totProdPurchased;
  int purchasedQuantity[200], purchasedCode[200], costPerProd[200];
  int totCustNum, customerCode;
  int i, j, k, menuInput, searchInput, flag = 0, bill = 0, disc = 0;
  float billGST;

  while (1)
  { // while(1) is true untill exit(0)
    printf("\n\n\n1. Add Customer\n");
    printf("2. Add Products\n");
    printf("3. Search Products\n");
    printf("4. Calculate Bill\n");
    printf("5. Discount Amout\n");
    printf("6. Print Recipt\n");
    printf("0. Exit Program\n");
    printf("\nWhat you want to do? : ");
    scanf("%d", &menuInput);
    printf("\n");

    // exitting program
    if (menuInput == 0)
    {
      exit(0);
    }

    // add customer
    else if (menuInput == 1)
    {
      printf("\nHow many customers you want to add? : ");
      scanf("%d", &totCustNum);
      for (i = 0; i < totCustNum; i++)
      {
        printf("\nAdding (%d)th customer", i + 1);
        printf("\n\nCustomer Name : ");
        scanf("%s", allCustomers[i].name);
        printf("\nCustomer Age : ");
        scanf("%d", &allCustomers[i].age);
        printf("\nCustomer Phone : ");
        scanf("%d", &allCustomers[i].phone);
        printf("\nCustomer Code : ");
        scanf("%d", &allCustomers[i].code);
      }
    }

    // add product
    else if (menuInput == 2)
    {
      // adding products to inventory
      printf("\nHow many products you want to add? : ");
      scanf("%d", &totProdNum);
      for (i = 0; i < totProdNum; i++)
      {
        printf("\nAdding (%d)th product", i + 1);
        printf("\n\nProduct Code : ");
        scanf("%d", &allProducts[i].code);
        printf("\nProduct Name : ");
        scanf("%s", allProducts[i].name);
        printf("\nProduct Price : ");
        scanf("%d", &allProducts[i].price);
      }
    }

    // search product
    else if (menuInput == 3)
    {

      // getting input
      printf("Enter product code or product price : ");
      scanf("%d", &searchInput);
      printf("\n");

      // searching for product
      for (int i = 0; i < totProdNum; i++)
      {
        if (searchInput == allProducts[i].code ||
            searchInput == allProducts[i].price)
        {
          searchprod.price = allProducts[i].price;
          searchprod.code = allProducts[i].code;
          strcpy(searchprod.name, allProducts[i].name);
          flag = 1;
          break;
        }
        else
        {
          flag = 0;
        }
      }

      // displaying product details
      if (flag == 1)
      {
        printf("Product Found and Details are :\n");
        printf("Product Code : %d\n", searchprod.code);
        printf("Product Name : %s\n", searchprod.name);
        printf("Product Price : %d\n", searchprod.price);
      }
      else
      {
        printf("\nProduct not found\n");
      }
    }

    // calculate bill
    else if (menuInput == 4)
    {
      // reading products
      printf("\nEnter no of products purchased: ");
      scanf("%d", &totProdPurchased);

      // display all the products
      printf("\n ***** Product Codes ***** \n");
      printf("--------------------------------------------------------\n");
      printf("S.N.|       NAME        |     CODE      |     PRICE     |\n");
      printf("--------------------------------------------------------\n");
      for (i = 0; i < totProdNum; i++)
      {
        printf("%d       %s                    %d             %d         \n",
               i + 1, allProducts[i].name, allProducts[i].code,
               allProducts[i].price);
      }
      printf("--------------------------------------------------------\n");

      for (i = 0; i < totProdPurchased; i++)
      {
        printf("\nEnter code of (%d)th product : ", i + 1);
        scanf("%d", &purchasedCode[i]);
        printf("\nHow much purchased? : ");
        scanf("%d", &purchasedQuantity[i]);
      }

      // copying purchased product list to a new array
      j = 0;
      for (k = 0; k < totProdPurchased; k++)
      {
        for (i = 0; i < totProdNum; i++)
        {
          // checking if product code exists
          if (allProducts[i].code == purchasedCode[k])
          {
            // creating a new array and storing product prices in it
            purchasedProducts[j].price = allProducts[i].price;
            purchasedProducts[j].code = allProducts[i].code;
            strcpy(purchasedProducts[j].name, allProducts[i].name);
            j++;
          }
        }
      }

      // finding total amount
      for (i = 0; i < totProdPurchased; i++)
      {
        prodTotalCost = purchasedProducts[i].price * purchasedQuantity[i];
        bill = bill + prodTotalCost;
      }

      // adding GST
      printf("\nAmount to be paid before discount without tax: %d\n", bill);
      billGST = bill + (0.05 * bill);
      printf("\nAmount to be paid before discount with tax: %f\n", billGST);
    }

    // discount calculation
    else if (menuInput == 5)
    {

      // discount for regular customers
      // keeping in mind that we only consider registered as regular customers
      printf("Enter customer code or phone number: ");
      scanf("%d", &customerCode);
      for (i = 0; i < totCustNum; i++)
      {
        if (customerCode == allCustomers[i].code ||
            customerCode == allCustomers[i].phone)
        {
          disc = 1;
          break;
        }
        else
        {
          disc = 0;
          break;
        }
      }
      discount(disc, billGST);

      // discount for bulk buying
      for (i = 0; i < totProdPurchased; i++)
      {
        if (purchasedQuantity[i] >= 10)
        {
          billGST = billGST - (0.1 * billGST); // 10% off
          printf("\nBulk order bill is : %f\n", billGST);
          break;
        }
      }

      // printing final bill
      printf("\n\n***** Total amount to be paid is : %f ******\n\n", billGST);
    }
    // print recipt
    else if (menuInput == 6)
    {
      // displaying recipt
      printf(" ***** FINAL BILL ***** \n");
      printf("--------------------------------------------------------\n");
      printf("S.N.| NAME   | CODE | QUANTITY | PRICE | TOTAL \n");
      printf("--------------------------------------------------------\n");
      for (i = 0; i < totProdPurchased; i++)
      {
        costPerProd[i] = purchasedQuantity[i] * purchasedProducts[i].price;
        printf("%d     %s     %d       %d        %d      %d \n", i + 1,
               purchasedProducts[i].name, purchasedProducts[i].code,
               purchasedQuantity[i], purchasedProducts[i].price,
               costPerProd[i]);
      }
      printf("\n--------------------------------------------------------\n");
      printf("\nTotal Cost excluding taxes and discount: %d\n", bill);
      printf("\nAmount to be Paid with 5 percent GST : %f\n", billGST);
      printf("\n******** Thankyou, Visit Again ********\n\n\n\n");
    }

    // otherwise
    else
    {
      error();
    }
  }
}

/* References
https://stackoverflow.com/questions/32313150/array-type-char-is-not-assignable
https://www.geeksforgeeks.org/exit0-vs-exit1-in-c-c-with-examples
https://www.javatpoint.com/array-of-structures-in-c
https://www.programiz.com/c-programming/c-pointers-arrays
https://data-flair.training/blogs/file-handling-in-c/
https://www.javatpoint.com/remove-an-element-from-an-array-in-c
https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/
https://www.scaler.com/topics/c/string-comparison-in-c/ */