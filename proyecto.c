#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

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

void ClearConsole() {
    #ifdef _WIN32
        system("cls"); 
    #else
        system("clear");  
    #endif
}

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
    FILE *fpProducts = fopen("Products.table", "wb");

    if(fp == NULL){
        printf("Error abriendo el archivo Products.dat");
        return;
    }
    if(fpProducts == NULL){
        printf("Error creando la tabla Products.table");
        return;
    }

    Products product;
    char line[1000];
    int counter = 0;

    while(fgets(line, sizeof(line), fp)){
        if(counter != 0){
            char *token = strtok(line, ","), temp[200] = "";
            product.ProductKey = (unsigned short int) atoi(token);

            token = strtok(NULL, ",");
            if(token[0] == '"'){
                while (token[strlen(token) - 1] != '"'){
                    strcat(token, strtok(NULL, ","));
                }
                strncpy(product.ProductName, token + 1, strlen(token));
                product.ProductName[strlen(product.ProductName) - 1] = '\0';
            } else {
                strcpy(product.ProductName, token);
            }

            token = strtok(NULL, ",");
            strcpy(product.Brand, token);

            token = strtok(NULL, ",");
            strcpy(product.Color, token);

            token = strtok(NULL, ",");
            if(token[0] == '"'){
                strcat(token, strtok(NULL, ","));
                product.UnitCostUSD = atof(strncpy(temp, token + 2, strlen(token)));
            } else {
                product.UnitCostUSD = atof(strncpy(temp, token + 1, strlen(token)));
            }

            token = strtok(NULL, ",");
            if(token[0] == '"'){
                strcat(token, strtok(NULL, ","));
                product.UnitPriceUSD = atof(strncpy(temp, token + 2, strlen(token)));
            } else {
                product.UnitPriceUSD = atof(strncpy(temp, token + 1, strlen(token)));
            }

            token = strtok(NULL, ",");
            strcpy(product.SubcategoryKey, token);

            token = strtok(NULL, ",");
            if(token[0] == '"'){
                strcat(token, strtok(NULL, ","));
                strncpy(product.Subcategory, token + 1, strlen(token));
                product.Subcategory[strlen(product.Subcategory) - 1] = '\0';
            } else {
                strcpy(product.Subcategory, token);
            }

            token = strtok(NULL, ",");
            strcpy(product.CategoryKey, token);

            token = strtok(NULL, ",");
            if(token[0] == '"'){
                strcat(token, strtok(NULL, ","));
                strncpy(product.Category, token + 1, strlen(token));
                product.Category[strlen(product.Category) - 1] = '\0';
            } else {
                strcpy(product.Category, token);
            }

            fwrite(&product, sizeof(product), 1, fpProducts);
        }
        counter++;
    }
    fclose(fp); fclose(fpProducts);
}

void CreateStoresTable(){
    FILE *fp = fopen("Stores.dat", "r");
    FILE *fpStores = fopen("Stores.table", "wb");

    if(fp == NULL){
        printf("Error abriendo el archivo Stores.dat");
        return;
    }
    if(fpStores == NULL){
        printf("Error creando la tabla Stores.table");
        return;
    }

    Stores store;
    char line[100] = "";
    int counter = 0;

    while(fgets(line, sizeof(line), fp)){
        if(counter != 0){
            char *token = strtok(line, ",");
            store.StoreKey = (unsigned short int) atoi(token);

            token = strtok(NULL, ",");
            strcpy(store.Country, token);

            token = strtok(NULL, ",");
            strcpy(store.State, token);

            token = strtok(NULL, ",");
            if(token[1] == '/' || token [2] == '/'){
                store.SquareMeters = 0;
            } else {
                store.SquareMeters = (unsigned short int) atoi(token);
                token = strtok(NULL, ",");
            }
            unsigned int day = 0, month = 0, year = 0;
            sscanf(token, "%u/%u/%u", &month, &day, &year);
            store.OpenDate.MM = (unsigned char) month;
            store.OpenDate.DD = (unsigned char) day;
            store.OpenDate.AAAA = (unsigned short int) year;

            fwrite(&store, sizeof(store), 1, fpStores);
    }
    counter++;
    }
    fclose(fp); fclose(fpStores);
}

void CreateExchangeRatesTable(){
    FILE *fp = fopen("Exchange_Rates.dat", "r");
    FILE *fpRates = fopen("Exchange_Rates.table", "wb");

    if(fp == NULL){
        printf("Error abriendo el archivo Exchange_Rates.dat");
        return;
    }
    if(fpRates == NULL){
        printf("Error creando la tabla Exchange_Rates.table");
        return;
    }

    ExchangeRates exchange;
    int counter = 0;
    char line[200];
    while(fgets(line, sizeof(line), fp)){
        if(counter != 0){
            char *token = strtok(line, ",");
            strcpy(exchange.Date, token);

            token = strtok(NULL, ",");
            strncpy(exchange.Currency, token, 3);
            exchange.Currency[3] = '\0';

            token = strtok(NULL, ",");
            exchange.Exchange = atof(token);

            fwrite(&exchange, sizeof(exchange), 1, fpRates);
        }
        counter++;
    }
    fclose(fp); fclose(fpRates);
}

void FirstPoint(){
    CreateCustomersTable();
    CreateExchangeRatesTable();
    CreateProductsTable();
    CreateSalesTable();
    CreateStoresTable();
}

void PrintMenu(){
    int security = 0;
    float option = 0;
    int program = 1;
    while(program){
        printf("\n\n\033[1mCompany Global Electronics Retailer\033[0m\n");
        printf("Options menu:\n");
        printf("0. Exit program\n");
        printf("1. Construction of the Database with the dataset tables\n");
        printf("2. List of What types of products does the company sell, and where are customers located?\n");
        printf("   2.1 Utility  bubbleSort\n");
        printf("   2.2 Utility  mergeSort\n");
        printf("3. List of Are there any seasonal patterns or trends for order volume or revenue?\n");
        printf("   3.1 Utility  bubbleSort\n");
        printf("   3.2 Utility  mergeSort\n");
        printf("4. List of How long is the average delivery time in days? Has that changed over time?\n");
        printf("   4.1 Utility  bubbleSort\n");
        printf("   4.2 Utility  mergeSort\n");
        printf("5. List of sales order by \"Customer Name\" + \"Order Date\" + \"ProductKey\":\n");
        printf("   5.1 Utility  bubbleSort\n");
        printf("   5.2 Utility  mergeSort\n");
        printf("\nWhat is your option: ");
        scanf("%f", &option);
        int value = option*10;
        switch (value)
        {
        case 0: 
            printf("\n\033[1mExiting program...\033[0m\n");
            program = 0;
            break;

        case 10:
            FirstPoint();
            security = 1;
            break;
        case 21:
            if(security){

            }else{
                printf("\nFirst create the dataset tables");
            }
            break;
        case 22:
            if(security){

            }else{
                printf("\nFirst create the dataset tables");
            }
            break;
        case 31:
            if(security){

            }else{
                printf("\nFirst create the dataset tables");
            }
            break;
        case 32:
            if(security){

            }else{
                printf("\nFirst create the dataset tables");
            }
            break;
        case 41:
            if(security){

            }else{
                printf("\nFirst create the dataset tables");
            }
            break;
        case 42:
            if(security){

            }else{
                printf("\nFirst create the dataset tables");
            }
            break;
        case 51:
            if(security){

            }else{
                printf("\nFirst create the dataset tables");
            }
            break;
        case 52:
            if(security){

            }else{
                printf("\nFirst create the dataset tables");
            }
            break;
        default:
            printf("\n\n\033[1mInvalid Option\033[0m\n");
            break;
        }
    }
}

int main(){
    ClearConsole();
    PrintMenu();
    return 0;
}