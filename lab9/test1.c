int globalCount; 

int square(int num) {
    return num * num;
}



void main(void) {
    int numbers[5];
    int i;
    int result;
    globalCount = 5;

    i = 0;
    while (i < globalCount) {
        write "Please enter number "; 
        write i;
        write ": ";
        read numbers[i];
        i = i + 1;
    }

    i = 0;
    while (i < globalCount) {
        result = square(numbers[i]);
        write "Square of ";
        write numbers[i];
        write " is: ";
        write result;
        if (result > 25) {
            write " (Result is greater than 25)";
        }
        write "\n";  
        i = i + 1;
    }
    return;
}
