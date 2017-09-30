/* Simple ad-hoc scanner for the calculator language.
    Michael L. Scott, 2008-2017.
*/

#include<iostream>
#include<ios>
#include <cstdlib> //not include this
#include <string>
#include <cctype>

#include "scan.h"
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::noskipws;


char token_image[100];

token scan() {
    static char c = ' ';
        /* next available char; extra (int) width accommodates EOF */
    int i = 0;              /* index into token_image */

    /* skip white space */
    while (isspace(c)) {
        //cin >> c;
        c=getchar();
    }
    cout << c << "\n";
    if (c == EOF)
        return t_eof;

    if (isalpha(c)) {
        do {
            token_image[i++] = c;
            c = getchar();
            //cin >> c;
            // cout << c << endl;
        } while (isalpha(c) || isdigit(c) || c == '_');
        // cout << "done" << endl;
        token_image[i] = '\0';
        if(token_image==string("read")) return t_read;
        else if (token_image==string("write")) return t_write;
        else if (token_image==string("do")) return t_do;
        else if (token_image==string("od")) return t_od;
        else if (token_image==string("if")) return t_if;
        else if (token_image==string("fi")) return t_fi;
        else if (token_image==string("check")) return t_check;
        //else if (token_image!=string(":=")) return t_gets;  //not colonequal
        else return t_id;
    }
    else if (isdigit(c)) {
      cout << "Digit\n";
        do {
            token_image[i++] = c;
            //cin >> c;
            c = getchar();
        } while (isdigit(c));
        token_image[i] = '\0';

        return t_literal;
    }
    else switch (c) {
        // case ':':
        //     //cin >> c;
        //     if (c != '=') {
        //         //fprintf(stderr, "error\n");
        //         cout << "error\n";
        //         exit(1);
        //     } else {
        //         //cin >> c;
        //         return t_gets;
        //     }
        //     break;
        /*
        case '+': //cin >> c; return t_add;
        case '-': //cin >> c; return t_sub;
        case '*': //cin >> c; return t_mul;
        case '/': //cin >> c; return t_div;
        case '(': //cin >> c; return t_lparen;
        case ')': //cin >> c; return t_rparen;
        */

        case '+': c = getchar(); return t_add;
        case '-': c = getchar(); return t_sub;
        case '*': c = getchar(); return t_mul;
        case '/': c = getchar(); return t_div;
        case '(': c = getchar(); return t_lparen;
        case ')': c = getchar(); return t_rparen;
        case '$': {
          c = getchar();
          if(c == '$'){
            c = getchar();
            return t_end;
          }else cout << "error\n";
        }
        //Relation operators added
        case ':':
          //cin >> c;
          c=getchar();
          // cout << c << endl;
          if (c == '='){
              //cin >> c;
              c=getchar();
              return t_gets;
            }
          cout << "error\n";

        case '<':
            //cin >> c;
            c=getchar();
            if (c == '>'){
                //cin >> c;
                c=getchar();
                return t_notequal;
            }else if(c == '='){
                //cin >> c;
                c=getchar();
                return t_smallerequal;
            }else return t_smaller;
        case '>':
            //cin >> c;
            c=getchar();
            if(c == '='){
                return t_greaterequal;
            }else return t_greater;
        case '=':
            //cin >> c;
            c=getchar();
            if(c == '='){
                return t_equal;
            }//remove double equal
            cout << "error\n";
        default:
            //printf("error\n");
            cout << "error\n";
            exit(1);
    }
}
