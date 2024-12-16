#include<stdio.h>

typedef struct {
    long int OrderNumber;
    unsigned char LineItems;
    struct {
        unsigned char MM;
        unsigned char DD;
        unsigned short int AAAA;
    } OrderDate;
    struct {
        unsigned char MM;
        unsigned char DD;
        unsigned short int AAAA;
    } DeliveryDate;
    unsigned int CustomerKey;
    unsigned short int StoreKey;
    unsigned short int ProductKey;
    unsigned short int Quantity;
    char CurrencyCode[3];
} Sales;

typedef struct {
    unsigned int CustomerKey;
    char Gender[8];
    char Name[40];
    char City[40];
    char StateCode[30];
    char State[30];
    unsigned int ZipCode;
    char Country[20];
    char Continent[20];
    struct {
        unsigned char MM;
        unsigned char DD;
        unsigned short int AAAA;
    } Birthday;
} Customers;

typedef struct {
    unsigned short int ProductKey;
    char ProductName[100];
    char Brand[30];
    char Color[15];
    float UnitCostUSD;
    float UnitPriceUSD;
    char SubcategoryKey[5];
    char Subcategory[50];
    char CategoryKey[3];
    char Category[35];
} Products;

typedef struct {
    unsigned short int StoreKey;
    char Country[35];
    char State[35];
    unsigned short int SquareMeters;
    struct {
        unsigned char MM;
        unsigned char DD;
        unsigned short int AAAA;
    } OpenDate;
} Stores;

typedef struct {
    char Date[11];
    char Currency[3];
    float Exchange;
} ExchangeRates;

int NumOfRecords(char file[], int size){
    FILE *fp = fopen(file, "rb");
    if(fp == NULL){
        printf("\nError al abrir el archivo %s.\n", file);
        return 0;
    }
    fseek(fp, 0, SEEK_END);
    long longFile = ftell(fp);
    fclose(fp);
    if(longFile == 0 || size == 0){
        return 0;
    }
    int total = longFile / size;
    return total;
}

void CreateSalesTable(){
    FILE *fp = fopen("Sales.dat", "r");
    FILE *fpSales = fopen("Sales.table", "wb");

    if(fp == NULL){
        printf("Error abriendo el archivo Sales.dat");
        return;
    }
    if(fpSales == NULL){
        printf("Error creando la tabla Sales.table");
        return;
    }

    Sales sale;
    char line[1024] = "";
    while(fgets(line, sizeof(line), fp)){
        char *token = strtok(line, ",");
        sale.OrderNumber = atol(token);

        token = strtok(NULL, ",");
        sale.LineItems = (unsigned char) atoi(token);
        
        token = strtok(NULL, ",");
        unsigned int day = 0, month = 0, year = 0;
        sscanf(token, "%u/%u/%u", &month, &day, &year);
        sale.OrderDate.MM = (unsigned char) month;
        sale.OrderDate.DD = (unsigned char) day;
        sale.OrderDate.AAAA = (unsigned short int) year;
        
        token = strtok(NULL, ",");
        if (token[0] == ' '){
            sale.DeliveryDate.MM = 0;
            sale.DeliveryDate.DD = 0;
            sale.DeliveryDate.AAAA = 0;
        } else {
            sscanf(token, "%u/%u/%u", &month, &day, &year);
            sale.DeliveryDate.MM = (unsigned char) month;
            sale.DeliveryDate.DD = (unsigned char) day;
            sale.DeliveryDate.AAAA = (unsigned short int) year;
        }
        
        token = strtok(NULL, ",");
        sale.CustomerKey = (unsigned long int) atoi(token);
        
        token = strtok(NULL, ",");
        sale.StoreKey = (unsigned short int) atoi(token);
        
        token = strtok(NULL, ",");
        sale.ProductKey = (unsigned short int) atoi(token);
        
        token = strtok(NULL, ",");
        sale.Quantity = (unsigned short int) atoi(token);
        
        token = strtok(NULL, ",");
        strcpy(sale.CurrencyCode, token);
        
        fwrite(&sale, sizeof(sale) ,1 ,fpSales);
    }
    fclose(fp); fclose(fpSales);
}

void CreateCustomersTable(){
    FILE *fp = fopen("Customers.dat", "r");
    FILE *fpCustomers = fopen("Customers.table", "wb");

    if(fp == NULL){
        printf("Error abriendo el archivo Customers.dat");
        return;
    }
    if(fpCustomers == NULL){
        printf("Error creando la tabla Customers.table");
        return;
    }

    Customers customer;
    char line[500] = "";
    int counter = 0;
    while(fgets(line, sizeof(line), fp)){
         if(counter != 0){
            char *token = strtok(line, ";");
            customer.CustomerKey = (unsigned long int) atoi(token);

            token = strtok(NULL, ";");
            strcpy(customer.Gender, token);

            token = strtok(NULL, ";");
            strcpy(customer.Name, token);

            token = strtok(NULL, ";");
            strcpy(customer.City, token);

            token = strtok(NULL, ";");
            strcpy(customer.StateCode, token);

            token = strtok(NULL, ";");
            strcpy(customer.State, token);

            token = strtok(NULL, ";");
            if (token[0] >= 48 && token[0] <= 57){
                customer.ZipCode = (unsigned long int) atoi(token);
                token = strtok(NULL, ";");
            } else {
                customer.ZipCode = 0;
            }
            strcpy(customer.Country, token);

            token = strtok(NULL, ";");
            strcpy(customer.Continent, token);

            token = strtok(NULL, ";");
            unsigned int day = 0, month = 0, year = 0;
            sscanf(token, "%u/%u/%u", &month, &day, &year);
            customer.Birthday.MM = (unsigned char) month;
            customer.Birthday.DD = (unsigned char) day;
            customer.Birthday.AAAA = (unsigned short int) year;

            fwrite(&customer, sizeof(customer), 1, fpCustomers);
    }
    counter++;
    }
    fclose(fp); fclose(fpCustomers);
}

void CreateProductsTable(){
    FILE *fp = fopen("Products.dat", "r");
    FILE *fpProducts = fopen("PRoducts.table", "wb");

    if(fp == NULL){
        printf("Error abriendo el archivo Customers.dat");
        return;
    }
    if(fpProducts == NULL){
        printf("Error creando la tabla Customers.table");
        return;
    }

    Products product;
    char line[1000];
    int counter;
    while(fgets(line, sizeof(line), fp)){
        
    }
}

void FirstPoint(){

}