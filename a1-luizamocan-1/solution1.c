
//problem 3
#include <stdio.h>

typedef struct {
    int content[100], length;
}vector;

void menu()
{
    /**
     Function that prints the menu, no parameters, nothing to return

     **/
    printf("1. Read a vector of numbers \n");
    printf("2. Print the Pascal triangle of dimension n of all combinations C(m,k)\n");
    printf("3. Find the longest contiguous subsequence of prime numbers.\n");
    printf("4. Print the vector\n");
    printf("0. Exit \n");

}

vector read_vector() {
    /**
     Function that reads a vector from the keyboard
     -no parameters
     -returns the vector
     **/

    vector Vector;
    Vector.length = 0;
    printf("Enter your elements\n");
    do {
        scanf("%d", &Vector.content[Vector.length++]);
    }while (Vector.content[Vector.length-1] != 0);
    Vector.length--;
    return Vector;
}

void print_vector(vector Vector) {

    /**
     Function that prints a vector in the console
     -no parameters
     -nothing to return
     **/
    for (int i = 0; i < Vector.length; i++) {
        printf("%d ", Vector.content[i]);
    }
    printf("\n");
}

int factorial(int n) {
    /**
     Function that computes n factorial
     -n:parameter to compute n!
     -returns the result of n!
     **/
    int product = 1;
    for (int i = 1; i <= n; i++) {
        product = product * i;
    }
    return product;
}

int combinations_by_m_taken_by_k(int m, int k) {
    /**
     Function that computes combinations of m taken by k
     -m: parameter that indicates the line that we are in the Pascal triangle
     -k: parameter that indicates the column that we are in the Pacsal triangle
     -returns the result of the combination
     **/
    int m_factorial=factorial(m);
    int k_factorial=factorial(k);
    int m_minus_k_factorial=factorial(m-k);

    int result=m_factorial/(k_factorial*m_minus_k_factorial);
    return result;

}

void print_Pascal_triangle(int n) {
    /**
     Function that prints the Pascal triangle of n rows
     -n:parameter that shows the number of rows
     -nothing to return
     **/
    for (int i=0; i<n; i++) {
        for (int s = 0; s < n - i - 1; s++) {
            printf(" ");
        }
        for (int j=0; j<=i; j++) {
            printf("%d ", combinations_by_m_taken_by_k(i,j));
            printf(" ");

        }
        printf("\n");
    }
}

int is_prime(int n) {
    /**
     Function that checks if a number is prime or not
     -n:parameter for which we check if it is prime
     -returns 1 if the number n is prime ,otherwise 0
     **/
    if (n<2) return 0;
    for (int d=2;d*d<=n;d++) {
        if (n%d==0) {
            return 0;
        }
    }
    return 1;
}

void LongestSubsequence(vector Vector, vector *new) {
    /**
    Function that finds the  longest contiguous subsequence of prime numbers
        in the given vector and stores it in the provided output vector

    -Vector :the input vector containing the sequence of numbers
    -new :pointer to a vector where the longest subsequence will be stored.
     **/
    vector Current;
    Current.length = 0;

    vector maximum;
    maximum.length = 0;

    for (int i = 0; i < Vector.length; i++) {
        if (is_prime(Vector.content[i])) {
            Current.content[Current.length] = Vector.content[i];
            Current.length++;
        }
        else {
            if (Current.length > maximum.length) {
                for (int j = 0; j < Current.length; j++) {
                    maximum.content[j] = Current.content[j];
                }
                maximum.length = Current.length;
            }
            Current.length = 0; // Reset for a new subsequence
        }
    }

    // check for the last sequence
    if (Current.length > maximum.length) {
        for (int j = 0; j < Current.length; j++) {
            maximum.content[j] = Current.content[j];
        }
        maximum.length = Current.length;
    }

    for (int j = 0; j < maximum.length; j++) {
        (*new).content[j] = maximum.content[j];
    }
    (*new).length = maximum.length;

}


int main() {
    //vector Vector=read_vector();
    //printf("length: %d\n", Vector.length);
    //print_vector(Vector);
    int option=-1;
    int number=0;
    vector Vector;

    while (1) {
        menu();
        scanf("%d", &option);
        switch (option) {
            case 1: {
                Vector = read_vector();
                printf("Elements were read successfully \n");
            }
            break;
            case 2: {
                printf("Enter the number of rows of the Pascal triangle:\n");
                scanf("%d", &number);
                printf("The Pascal triangle of %d rows is:\n", number);
                print_Pascal_triangle(number);
            }
            break;
            case 3: {
                vector subsequence;
                LongestSubsequence(Vector, &subsequence);
                if (subsequence.length ==0) {
                    printf("No prime numbers found \n");
                }
                else{
                    printf("The longest subsequence of prime numbers is: \n");
                    print_vector(subsequence);
                }

                break;
            }

            case 4: {
                printf("The elements are:\n ");
                print_vector(Vector);
            }
            break;
            default:
                break;


        }
        if (option ==0) break;
    }


    return 0;
}