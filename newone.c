#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>


int addProduct();     // to add product.
int getCount();       // to get count of records.
int DisplayProduct(); // Display products.
int dispHsale();      // Display higest sale records.
int loadData();       // to load data on the RAM.
int writefile();      // to write data into the file.
int DeletProd();      // to delete products. 
int ZeroQuantity();   // to display zero ouantity.
int purchase();       // to purchase.
int editProduct();    // to edit products.



struct product // getting data from the file and store data to file. 
	{
	int records;
	char id[10];   // product code/no.
	char name[20]; // product name.
	int  quantity; // remaining quantity of product. Subtract from the original quantity the quantity purchased.
    int  numSold;  // initially zero, when no purchase yet.
	float price;   // price of one piece of product.
	int discount;  // discount for this product.
	float sales;   // accumulated sales, total sales for this product.
	};
	
struct  product prod[30]; //Size of Structure 



int main(){ // Main Function
	
time_t t;   // not a primitive datatype
time(&t);

int user; 

do {	

	printf("\n");
	printf("\t\t\t  ============================================\n");
	printf("\t\t\t   <------ PRODUCT INVENTORY PROGRAM ------>\n");
	printf("\t\t\t  ============================================\n");
	printf("\t\t\t  Date and time: %s", ctime(&t));

	printf("\n\nPress:");
	printf("\n 1.) Input new product record.");
	printf("\n 2.) Edit a Product.");
	printf("\n 3.) Delete a Product");
	printf("\n 4.) Display all existing product.");
	printf("\n 5.) Make a purchase.");
	printf("\n 6.) Display the product record with highest sale.");
	printf("\n 7.) Display all product with zero quantity");
	printf("\n 8.) Exit the program.");
	printf("\nChoice--> "); 
	scanf("%d",&user);
	
	switch(user){
	
		case 1:
		addProduct(); // add Product
		break;
		
		case 2:
		editProduct(); // Edit Product
		break;	
		
		case 3:
		DeletProd(); // Delete Product
		break;
		
		case 4:
		DisplayProduct(); // Display Product
		break;
		
		case 5:
		purchase(); // Purchase Product
		break;
		
		case 6:
		dispHsale(); // Displa Higest Sale
		break;
		
		case 7:
		ZeroQuantity(); // Displa zero Quantity
		break;
		
		case 8:
		printf("Exit");
		exit(1); // Exit from the system
        break;
		
		
			
	}
    
   }while(user!=8); // infinite loop until the user will choose number8 .
  printf("Thankyou for using this program");
}

//===================================== 1st Function =========================================
int addProduct(){ //to add product into the file.
	
    FILE *cfptr;
    cfptr = fopen("textingFile.txt","a");
    char id[10];
    prod[0].records = getCount(); // getting the current count of records that are available in the fill.
    //loadData();
    
    
    //printf("%s",id);
    
    if(cfptr==NULL){
 	printf("Fille cannot be open");
 	main();
 }else{
 	
 	loadData();
 	printf("Enter the product id:");
 	scanf("%s",id);
 	
 	int i;
 	for(i=0; i<prod[0].records; i++){
 		if(strcmp(id,prod[i].id)==0){
 			
 			printf("Id is available. Try again!!\n");
 			printf("\n");
 		
 			main();
 			//exit(1);
		 }
		 
	 }
	 
	 
	int n;
	for(n=0; n<10; n++){
		prod[0].id[n]= id[n];
	} 
 	
 	printf("Enter the product name:");
 	scanf("%s", prod[0].name);
 	
 	printf("Enter the quantity:");
 	scanf("%d", &prod[0].quantity);
 	
 	prod[0].numSold = 0;
 	
 	printf("Enter the price:");
 	scanf("%f", &prod[0].price);
 	
 	printf("Enter the discount:");
 	scanf("%d",&prod[0].discount);
 	
 	
 	prod[0].sales = 0; 	
 	
 	fprintf(cfptr, "%s\n %s\n %d\n %d\n %0.2f\n %d\n %0.2f\n", prod[0].id, prod[0].name, prod[0].quantity, prod[0].numSold, prod[0].price, prod[0].discount,prod[0].sales); //Write data into the file.
 	prod[0].records++;// update count
 	
       FILE *co;
       co = fopen("count.txt","w");
    
       fprintf(co, "%d", prod[0].records); // write count into the count text file.
       fclose(co);
    
       fclose(cfptr);
 }	
 
 
}
//========================================= 2nd Function =======================================

int DisplayProduct(){ // Display the all of records that are in the  file
	
	
   FILE *readf;
   readf= fopen("textingFile.txt","r");
   
   
   int n;
   n = getCount(); // Getting the count of records 
   printf("------------------------------------------------------------------------------------\n");
   printf("S.N.|    NAME     |  PROD ID  |  QUANTITY | PROD SOLD |  PRICE  | DISCOUNT | SALES |\n");
   printf("------------------------------------------------------------------------------------\n");
   int y;
   for(y=0; y<n; y++){
   
   fscanf(readf,"%s", prod[y].id);
   fscanf(readf,"%s", prod[y].name);
   fscanf(readf,"%d", &prod[y].quantity);
   fscanf(readf,"%d", &prod[y].numSold);
   fscanf(readf,"%f", &prod[y].price);
   fscanf(readf,"%d", &prod[y].discount);
   fscanf(readf,"%f", &prod[y].sales);
   
  
   
   printf("%d     %-10s       %-8s     %-5d      %-3d       %-6.2f    %-5d%%    $%.2lf\n",y+1,prod[y].name,prod[y].id,prod[y].quantity,prod[y].numSold,prod[y].price,prod[y].discount,prod[y].sales); //Display all of records that are in the file.
   
   }
  
 
  fclose(readf);	
	
	
}


int getCount(){ // getting count of records that are in the file.
	
 FILE *co1;
 co1 = fopen("count.txt","r");
 
 int c;
 fscanf(co1,"%d", &c);
 prod[0].records=c;
 
 fclose(co1);
 
 return c;
}

//==================================== 3d Function ==================================================


int loadData(){ // load all of data on the RAM from the file. 
   FILE *readf;
   readf= fopen("textingFile.txt","r");
   
   
   int n;
   n = getCount();
   
   int y;
   for(y=0; y<n; y++){
   
   fscanf(readf,"%s", prod[y].id);
   fscanf(readf,"%s", prod[y].name);
   fscanf(readf,"%d", &prod[y].quantity);
   fscanf(readf,"%d", &prod[y].numSold);
   fscanf(readf,"%f", &prod[y].price);
   fscanf(readf,"%d", &prod[y].discount);
   fscanf(readf,"%f", &prod[y].sales);
   
   }	
}





int writefile()//write file function
{
    int i;
    int count;
    FILE *f;
    f = fopen("textingFile.txt", "w");  // ayaw i append; change from f = fopen("inventory.txt", "a");
    if (f == NULL)
        return -1;			
    count = getCount();
    for (i = 0; i < count; ++i) // writing all the details from all the function to the text file.
    {
        // Changed
        fputs(prod[i].id, f);
        fprintf(f, "\n");
        fputs(prod[i].name, f);
        fprintf(f, "\n");
        fprintf(f, "%d\n", prod[i].quantity);
        fprintf(f, "%d\n", prod[i].numSold);
        fprintf(f, "%f\n", prod[i].price);
        fprintf(f, "%d\n", prod[i].discount);
        fprintf(f, "%f\n", prod[i].sales);
    }
    fclose(f);
    return 0;
}

//================================== 4th Function ========================================================
int DeletProd(){ // to delete the record that you need.

int count;
int i;
int records;
char id[10];
printf("Enter the id:");
scanf("%s",id);
loadData();
count = getCount();
records = count;
FILE *f;
f = fopen("textingFile.txt", "w"); 
for(i=0; i<count; i++){

  if(strcmp(id,prod[i].id)!=0){ // compare the id with user given id.
  
        fputs(prod[i].id, f);
        fprintf(f, "\n");
        fputs(prod[i].name, f);
        fprintf(f, "\n");
        fprintf(f, "%d\n", prod[i].quantity);
        fprintf(f, "%d\n", prod[i].numSold);
        fprintf(f, "%f\n", prod[i].price);
        fprintf(f, "%d\n", prod[i].discount);
        fprintf(f, "%f\n", prod[i].sales);
       
  }else{
  
       FILE *co;
       co = fopen("count.txt","w");
       
       fprintf(co, "%d",records-1);
       fclose(co);
  
  }

}

 fclose(f);
 return 0;
}
//========================================== 5th Function ===========================================
int ZeroQuantity(){ // to display zero quantity records.

    FILE *readf;
    readf= fopen("textingFile.txt","r");

    int n;
    n =  getCount();

    int y;
    for(y=0; y<n; y++){

   fscanf(readf,"%s", prod[y].id);
   fscanf(readf,"%s", prod[y].name);
   fscanf(readf,"%d", &prod[y].quantity);
   fscanf(readf,"%d", &prod[y].numSold);
   fscanf(readf,"%f", &prod[y].price);
   fscanf(readf,"%d", &prod[y].discount);
   fscanf(readf,"%f", &prod[y].sales);

    if(prod[y].quantity==0){
printf("\nS.N: %d\nProduct Id: %s\nName of the product: %s\nQuantity left: %d\nNumber of product sold: %d\nPrice of the product: %0.2f\nDiscount of the product: %d\nTotal Sales: %0.2f\n", y+1, prod[y].id, prod[y].name, prod[y].quantity, prod[y].numSold, prod[y].price, prod[y].discount,prod[y].sales);
    }
   }
  fclose(readf);
}

//===================================== 6th Function =====================================================

int purchase() // to purchase products.
{   
    int qty,y;
    char i[10];//id
    float Cost,Sales;
    int n,z=0;
    
    n=getCount();
    loadData();
    
    printf("Sell an item\n");
    printf("Enter product ID:");
    scanf("%s",i);
    for(y=0; y<n; y++){
    	if(strcmp(i,prod[y].id)==0) {
    	    z++;
    	printf("Item Found! Containing:\n");
    	printf("\n");
   		printf("Product name: %s\n",prod[y].name);
		printf("Price:$ %.2f\n",prod[y].price);
		printf("Quantity: %d\n",prod[y].quantity);
		
		printf("\n");	
        printf("Enter  the quantity you want to by: ");
        scanf("%i",&qty);
   
   			if(prod[y].quantity>=qty)
   			{
		
    		//After buying update 
    		prod[y].quantity=prod[y].quantity-qty;
    		//updating sold item
    		prod[y].numSold=prod[y].numSold+qty;
    		//price Calculation
    		Cost=prod[y].price*qty;
   		Sales = Cost - (Cost*prod[y].discount)/100.0;
   		 prod[y].sales+=Sales;
   		    
   			printf("Updated Quantity: %d\nsold: %d\nCost :$  %.2f\nSales :$ %0.2f\n", prod[y].quantity,prod[y].numSold,Cost,Sales);
  			writefile();
           }
          else
		  {
		    printf("Insufficient quantity!");         
		  }
		  
		  } 
	    }

        
        if(z==0)
        {
        	
        	printf("Item not found!");
		}

        	

	
}
//========================================= 7th Funtion =======================================
int dispHsale(){ //to display higest sale.
    loadData();
	
   int  i , count,  s_n=0 ;
   float high=0.0;
	 
   printf(" \t\t\t\t *****  INVENTORY *****\n");
   printf("**  HIGH SALES PRODUCT **\n");
   printf("------------------------------------------------------------------------------------\n");
   printf("S.N.|    NAME     |  PROD ID  |  QUANTITY | PROD SOLD |  PRICE  | DISCOUNT | SALES |\n");
   printf("------------------------------------------------------------------------------------\n"); 
	
	count = getCount();
	for (i=0; i<count; i++){
		if (prod[i].sales >= high){
			high = prod[i].sales;
		}
	}
	
	for (i=0; i < count; i++){
		if (prod[i].sales == high && prod[i].sales !=0){
		s_n = s_n + 1; // to count serial number
		printf("%d     %-10s       %-8s     %-5d      %-3d       %-6.2f    %-5d%%    %.2lf\n",s_n,prod[i].name,prod[i].id,prod[i].quantity,prod[i].numSold,prod[i].price,prod[i].discount,prod[i].sales);
		}
	}
	
}

//====================================================== 8th Function ===============================================
int editProduct(){ //to edit the product
	char id1[10];
	int h;
	int count;
	int z=0;
	
	
	
	loadData();
	count=getCount();
	
	printf("Enter the product Id that you want to update: ");
	scanf("%s",id1);
	
	for(h=0; h<count; h++){
	
	if(strcmp(id1,prod[h].id)==0){
	  z++;
	
	  
 	  printf("Enter the product name:");
 	  scanf("%s", prod[h].name);
 	
 	  printf("Enter the quantity:");
 	  scanf("%d", &prod[h].quantity);
 	
 	  printf("Enter the price:");
 	  scanf("%f", &prod[h].price);
 	
 	  printf("Enter the discount:");
 	  scanf("%d", &prod[h].discount);
 	  
 	  printf("\n");
 	  printf("=====================================\n");
 	  printf("ID: %s\n",prod[h].id);
 	  printf("Name was updated as: %s\n",prod[h].name);
 	  printf("Quantity was updated as:%d\n",prod[h].quantity);
 	  printf("Price was updated as:$ %0.2f\n",prod[h].price);
 	  printf("Discount was updated as: %d\n",prod[h].discount);
 	  printf("=====================================\n");
 	  
 	 
 	  
 	  writefile();
 	  
 	  printf("Record Updated...!\n");
 	  
 			
	}
	
	 }

if (z==0){
    
       printf("\nID is not available");
    }
}

    



