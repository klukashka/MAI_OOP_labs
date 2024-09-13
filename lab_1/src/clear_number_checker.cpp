bool number_is_clear(long long int number){
    if (number < 0){
        number *= -1;
    }
    long long int copied_number = number;
    int number_size = 0;
    int last_digit;
    while (number > 0){
        last_digit = number % 10;
        number /= 10;
        if ((number % 10) > last_digit){
            return false;
        }
    }
    return true;
}