/*
 * 写在前面：
 * 这个程序用于求解关于x和y的正整数不定方程a^x + b = c^y，其中a, b, c为给定正整数，a, c >= 2
 * 为了将不同的模块拼在一起，这个（庞大的）源文件可读性非常差
 * 如果希望了解这个项目，请移步https://github.com/parkcai/Diophantine
 */

const int endl = 10;
const int space = 32;
const int left_parenthesis = 40;
const int right_parenthesis = 41;
const int period = 46;
const int comma = 44;
const int percentage = 37;
const int equals = 61;
const int hat = 94;
int null[1] = {0};
int newline[1] = {10};
int string_x[2] = {120, 0};
int strlen_x = 2;
int string_y[2] = {121, 0};
int strlen_y = 2;
int string_z[2] = {122, 0};
int strlen_z = 2;
int string_u[2] = {117, 0};
int strlen_u = 2;
int string_v[2] = {118, 0};
int strlen_v = 2;
int assertion = 1;



void print_line(int line[]){
    if (!line[0]) return;
    int i = 0;
    while (line[i] != endl) { 
        putch(line[i]);   
        i = i + 1;   
    }
    putch(endl);
}

void print_word(int word[]) {
    int i = 0;
    while (word[i]) { 
        putch(word[i]);   
        i = i + 1;   
    }
}

void print_line_with_ddd(int line[], int arg1, int arg2, int arg3) {
    if (!line[0]) return;
    int i = 0;
    int count = 1;
    while (line[i] != endl) {
        if (line[i] != percentage) {
            putch(line[i]);   
            i = i + 1; 
        }else{
            if (count == 1) {
                putint(arg1);
                i = i + 2; 
                count = count + 1;
            }else if (count == 2) {
                putint(arg2);
                i = i + 2; 
                count = count + 1;
            }else{
                putint(arg3);
                i = i + 2; 
            }
        }
    }
    putch(endl);
}

void print_line_with_dsd(int line[], int arg1, int arg2[], int arg3) {
    if (!line[0]) return;
    int i = 0;
    int count = 1;
    while (line[i] != endl) {
        if (line[i] != percentage) {
            putch(line[i]);   
            i = i + 1; 
        }else{
            if (count == 1) {
                putint(arg1);
                i = i + 2; 
                count = count + 1;
            }else if (count == 2) {
                print_word(arg2);
                i = i + 2; 
                count = count + 1;
            }else{
                putint(arg3);
                i = i + 2; 
            }
        }
    }
    putch(endl);
}

void print_line_with_dsdds(int line[], int arg1, int arg2[], int arg3, int arg4, int arg5[]) {
    if (!line[0]) return;
    int i = 0;
    int count = 1;
    while (line[i] != endl) {
        if (line[i] != percentage) {
            putch(line[i]);   
            i = i + 1; 
        }else{
            if (count == 1) {
                putint(arg1);
                i = i + 2; 
                count = count + 1;
            }else if (count == 2) {
                print_word(arg2);
                i = i + 2; 
                count = count + 1;
            }else if (count == 3) {
                putint(arg3);
                i = i + 2; 
                count = count + 1;
            }else if (count == 4) {
                putint(arg4);
                i = i + 2; 
                count = count + 1;
            }else{
                print_word(arg5);
                i = i + 2;
            }
        }
    }
    putch(endl);
}

void print_line_with_sdsd(int line[], int arg1[], int arg2, int arg3[], int arg4) {
    if (!line[0]) return;
    int i = 0;
    int count = 1;
    while (line[i] != endl) {
        if (line[i] != percentage) {
            putch(line[i]);   
            i = i + 1; 
        }else{
            if (count == 1) {
                print_word(arg1);
                i = i + 2; 
                count = count + 1;
            }else if (count == 2) {
                putint(arg2);
                i = i + 2; 
                count = count + 1;
            }else if (count == 3) {
                print_word(arg3);
                i = i + 2; 
                count = count + 1;
            }else{
                putint(arg4);
                i = i + 2; 
                count = count + 1;
            }
        }
    }
    putch(endl);
}

void print_line_with_dd(int line[], int arg1, int arg2) {
    if (!line[0]) return;
    int i = 0;
    int count = 1;
    while (line[i] != endl) {
        if (line[i] != percentage) {
            putch(line[i]);   
            i = i + 1; 
        }else{
            if (count == 1) {
                putint(arg1);
                i = i + 2; 
                count = count + 1;
            }else{
                putint(arg2);
                i = i + 2; 
                count = count + 1;
            }
        }
    }
    putch(endl);
}

void print_line_with_ss(int line[], int arg1[], int arg2[]) {
    if (!line[0]) return;
    int i = 0;
    int count = 1;
    while (line[i] != endl) {
        if (line[i] != percentage) {
            putch(line[i]);   
            i = i + 1; 
        }else{
            if (count == 1) {
                print_word(arg1);
                i = i + 2; 
                count = count + 1;
            }else{
                print_word(arg2);
                i = i + 2; 
                count = count + 1;
            }
        }
    }
    putch(endl);
}

void print_line_with_sddsdd(int line[], int arg1[], int arg2, int arg3, int arg4[], int arg5, int arg6) {
    if (!line[0]) return;
    int i = 0;
    int count = 1;
    while (line[i] != endl) {
        if (line[i] != percentage) {
            putch(line[i]);   
            i = i + 1; 
        } else {
            if (count == 1) {
                print_word(arg1);
                i = i + 2; 
                count = count + 1;
            } else if (count == 2) {
                putint(arg2);
                i = i + 2; 
                count = count + 1;
            } else if (count == 3) {
                putint(arg3);
                i = i + 2; 
                count = count + 1;
            } else if (count == 4) {
                print_word(arg4);
                i = i + 2; 
                count = count + 1;
            } else if (count == 5) {
                putint(arg5);
                i = i + 2; 
                count = count + 1;
            } else {
                putint(arg6);
                i = i + 2;
                count = count + 1;
            }
        }
    }
    putch(endl);
}

void print_line_with_sdd(int line[], int arg1[], int arg2, int arg3) {
    if (!line[0]) return;
    int i = 0;
    int count = 1;
    while (line[i] != endl) {
        if (line[i] != percentage) {
            putch(line[i]);   
            i = i + 1; 
        } else {
            if (count == 1) {
                print_word(arg1);
                i = i + 2; 
                count = count + 1;
            } else if (count == 2) {
                putint(arg2);
                i = i + 2; 
                count = count + 1;
            } else {
                putint(arg3);
                i = i + 2; 
                count = count + 1;
            }
        }
    }
    putch(endl);
}

void print_line_with_d(int line[], int arg1) {
    if (!line[0]) return;
    int i = 0;
    int count = 1;
    while (line[i] != endl) {
        if (line[i] != percentage) {
            putch(line[i]);   
            i = i + 1; 
        } else {
            if (count == 1) {
                putint(arg1);
                i = i + 2; 
                count = count + 1;
            }
        }
    }
    putch(endl);
}

void print_line_with_sd(int line[], int arg1[], int arg2) {
    if (!line[0]) return;
    int i = 0;
    int count = 1;
    while (line[i] != endl) {
        if (line[i] != percentage) {
            putch(line[i]);   
            i = i + 1; 
        } else {
            if (count == 1) {
                print_word(arg1);
                i = i + 2; 
                count = count + 1;
            }else {
                putint(arg2);
                i = i + 2;
            }
        }
    }
    putch(endl);
}

void print_line_with_ssdsdds(int line[], int arg1[], int arg2[], int arg3, int arg4[], int arg5, int arg6, int arg7[]) {
    if (!line[0]) return;
    int i = 0;
    int count = 1;
    while (line[i] != endl) {
        if (line[i] != percentage) {
            putch(line[i]);   
            i = i + 1; 
        } else {
            if (count == 1) {
                print_word(arg1);
                i = i + 2; 
                count = count + 1;
            } else if (count == 2) {
                print_word(arg2);
                i = i + 2; 
                count = count + 1;
            } else if (count == 3) {
                putint(arg3);
                i = i + 2; 
                count = count + 1;
            } else if (count == 4) {
                print_word(arg4);
                i = i + 2; 
                count = count + 1;
            } else if (count == 5) {
                putint(arg5);
                i = i + 2; 
                count = count + 1;
            }else if (count == 6) {
                putint(arg6);
                i = i + 2; 
                count = count + 1;
            } else {
                print_word(arg7);
                i = i + 2;
                count = count + 1;
            }
        }
    }
    putch(endl);
}

void assert(int expr, int err_info[]) {
    assertion = expr;
    if (!assertion) {
        print_line(err_info);
    }
}

const int prime_list[168] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};

int greatest_common_divisor(int n, int m) {
    //"Invalid input of greatest_common_divisor!"
    int array1[42] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 103, 114, 101, 97, 116, 101, 115, 116, 95, 99, 111, 109, 109, 111, 110, 95, 100, 105, 118, 105, 115, 111, 114, 33, 10};
    assert(n >= 1 && m >= 1, array1);
    if(!assertion) return 0;
    int temp;
    while (m != 0) {
        temp = m;
        m = n % m;
        n = temp;
    }
    return n;
}

int least_common_multiple(int n, int m) {
    //"Invalid input of least_common_multiple!"
    int array1[40] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 108, 101, 97, 115, 116, 95, 99, 111, 109, 109, 111, 110, 95, 109, 117, 108, 116, 105, 112, 108, 101, 33, 10};
    assert(n >= 1 && m >= 1, array1);
    if(!assertion) return 0;
    int d = greatest_common_divisor(n, m);
    return n * (m / d);
}

int get_power_cycle_mod(int n, int m) {
    //"Invalid input of get_power_cycle_mod!"
    int array1[38] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 103, 101, 116, 95, 112, 111, 119, 101, 114, 95, 99, 121, 99, 108, 101, 95, 109, 111, 100, 33, 10};
    assert(n >= 2 && m >= 1, array1);
    if(!assertion) return 0;
    assert(greatest_common_divisor(n,m) == 1, array1);
    if(!assertion) return 0;
    m = m % n;
    int m0 = m;
    if (m == 1) return 1;
    int result = 1;
    while (m != 1) {
        m = (m * m0) % n;
        result = result + 1;
    }
    return result;
}

int get_power_position_mod(int n, int m, int k) {
    //"Invalid input of get_power_position_mod!"
    int array1[41] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 103, 101, 116, 95, 112, 111, 119, 101, 114, 95, 112, 111, 115, 105, 116, 105, 111, 110, 95, 109, 111, 100, 33, 10};
    assert(n >= 2 && m >= 1 && k >= 0, array1);
    if(!assertion) return 0;
    assert(greatest_common_divisor(n,m) == 1, array1);
    if(!assertion) return 0;
    k = k % n;
    if (k == 1) return 0;
    m = m % n;
    int m0 = m;
    int result = 1;
    while (m != 1) {
        if (k == m) return result;
        m = (m * m0) % n;
        result = result + 1;
    }
    return -1;
}

int is_prime(int n) {
    //"Invalid input of is_prime!"
    int array1[27] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 105, 115, 95, 112, 114, 105, 109, 101, 33, 10};
    assert(n >= 1, array1);
    if(!assertion) return 0;
    if (n == 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    int i = 5;
    while (i * i <= n) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0; 
        }
        i = i + 6;
    }
    return 1; 
}

int power(int base, int exp, int mod) {
    //"Invalid input of power!"
    int array1[24] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 112, 111, 119, 101, 114, 33, 10};
    assert(base >= 1 && exp >= 0 && (mod >= 2 || mod == -1), array1);
    if(!assertion) return 0;
    int res = 1, i = 0;
    while (i < exp) {
        res = res * base;
        if (mod != -1) {
            res = res % mod;
        }
        i = i + 1;
    }
    return res;
}

int contain_undividable_prime_part(int d, int x) {
    //"Invalid input of contain_undividable_prime_part!"
    int array1[49] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 99, 111, 110, 116, 97, 105, 110, 95, 117, 110, 100, 105, 118, 105, 100, 97, 98, 108, 101, 95, 112, 114, 105, 109, 101, 95, 112, 97, 114, 116, 33, 10};
    assert(d >= 1 && x >= 1, array1);
    if(!assertion) return 0;
    int i = 2;
    while (i <= d) {
        if (d % i == 0 && is_prime(i)) { 
            if (x % i != 0) { 
                return 1; 
            }
        }
        i = i + 1;
    }
    return 0; 
}

int get_power_times_over(int M, int a){
    //"Invalid input of get_power_times_over!"
    int array1[39] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 103, 101, 116, 95, 112, 111, 119, 101, 114, 95, 116, 105, 109, 101, 115, 95, 111, 118, 101, 114, 33, 10};
    assert(a >= 2 && M >= 1, array1);
    if(!assertion) return 0;
    int n = 1, a0 = a;
    while (a <= M) {
        a = a * a0;
        n = n + 1;
    }
    return n;
}

int get_degree_wrt(int p, int N) {
    int res = 0;
    while (N % p == 0) {
        N = N / p;
        res = res + 1;
    }
    return res;
}

int a_v1;
int b_v1;
int c_v1;
int abc_set_status_v1 = 0;
int x_name_v1[10] = {120, 0};
int y_name_v1[10] = {121, 0};
int xy_name_set_status_v1 = 1;
int solution_v1[200000];
int solution_v1_pointer;
int solution_v1_length;
int solver_v1_success;
int search_threshold_v1 = 2100000000;
// 这两个设小了可能会导致求解失败
// 设大了可能导致那些需要多试几个方案的方程在一个方案上耗费的时间过长
int mod_threshold_v1 = 200000;
int max_trial_num_v1 = 25;
int disproof_priorlist_prime[100];
int disproof_priorlist_power[100];
int disproof_priorlist_type[100]; // a = 1, c = 3
int disproof_prime;
int disproof_power;
int disproof_type;
int disproof_priorlist_length = 0;
int solution_max_length_v1 = 200000;
int verbose = 0;
int disable_front_mode = 0;
int disable_back_mode = 0;

void set_abc_v1(int a, int b, int c) {
    //"Invalid input of set_abc_v1!"
    int array1[29] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 115, 101, 116, 95, 97, 98, 99, 95, 118, 49, 33, 10};
    assert(a >= 2 && c >= 2 && b >= 1, array1);
    if (!assertion) return;
    a_v1 = a;
    b_v1 = b;
    c_v1 = c;
    abc_set_status_v1 = 1;
}

void set_xy_name_v1(int x_name[], int y_name[], int x_name_len, int y_name_len) {
    int index = 0;
    int temp;
    int x_encounter_zero = 0;
    int y_encounter_zero = 0;
    while (index < 10) {
        if (!x_encounter_zero && index < x_name_len) {
            temp = x_name[index];
            x_name_v1[index] = temp;
            if (!temp) x_encounter_zero = 1;
        }
        if (!y_encounter_zero && index < y_name_len) {
            temp = y_name[index];
            y_name_v1[index] = temp;
            if(!temp) y_encounter_zero = 1;
        }
        index = index + 1;
    }
    //"Invalid input of set_xy_name_v1!"
    int array1[33] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 115, 101, 116, 95, 120, 121, 95, 110, 97, 109, 101, 95, 118, 49, 33, 10};
    assert(x_encounter_zero && y_encounter_zero, array1);
    if(!assertion) return;
    xy_name_set_status_v1 = 1;
}

void write_solution_v1(int x) {
    //"[Solver V1] solution pointer out of legal range!"
    int array1[49] = {91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 115, 111, 108, 117, 116, 105, 111, 110, 32, 112, 111, 105, 110, 116, 101, 114, 32, 111, 117, 116, 32, 111, 102, 32, 108, 101, 103, 97, 108, 32, 114, 97, 110, 103, 101, 33, 10};
    assert(solution_v1_pointer >= 0 && solution_v1_pointer < solution_max_length_v1, array1);
    if(!assertion) return;
    solution_v1[solution_v1_pointer] = x;
    solution_v1_pointer = solution_v1_pointer + 1;
    solution_v1_length = solution_v1_length + 1;
    solution_v1[0] = solution_v1_length;
}

int read_solution_v1() {
    //"[Solver V1] solution pointer out of legal range!"
    int array1[49] = {91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 115, 111, 108, 117, 116, 105, 111, 110, 32, 112, 111, 105, 110, 116, 101, 114, 32, 111, 117, 116, 32, 111, 102, 32, 108, 101, 103, 97, 108, 32, 114, 97, 110, 103, 101, 33, 10};
    assert(solution_v1_pointer >= 0 && solution_v1_pointer < solution_max_length_v1, array1);
    if(!assertion) return 0;
    solution_v1_pointer = solution_v1_pointer + 1;
    return solution_v1[solution_v1_pointer-1];
}

void resume_solution_v1(int solution_v1_pointer_backup) {
    solution_v1_length = solution_v1_length - (solution_v1_pointer - solution_v1_pointer_backup);
    solution_v1_pointer = solution_v1_pointer_backup;
}

void Solve_Diophantine1_II_disproof_A() {
    solver_v1_success = 0;
    if (disable_back_mode) return;
    int M = power(disproof_prime, disproof_power, -1);
    if(!assertion) return;
    int R = b_v1 % M;
    // c ^ y = R (mod M)
    write_solution_v1(c_v1);
    if(!assertion) return;
    write_solution_v1(R);
    if(!assertion) return;
    write_solution_v1(M);
    if(!assertion) return;
    int k = get_power_cycle_mod(M, c_v1);
    if(!assertion) return;
    int yr = get_power_position_mod(M, c_v1, R);
    if(!assertion) return;
    // c ^ y = R (mod M) is impossible
    if (yr == -1) {
        write_solution_v1(yr);
        if(!assertion) return;
        solver_v1_success = 1;

    // c ^ y = R (mod M) => y = yr (mod k)
    }else{
        // if (k == 1) return;
        if (k < 10) return;
        write_solution_v1(yr);
        if(!assertion) return;
        write_solution_v1(k);
        if(!assertion) return;
        int solution_v1_pointer_backup = solution_v1_pointer;
        int n = 1, P = n * k + 1;
        int trial_num = 0;
        while (P < mod_threshold_v1 && trial_num < max_trial_num_v1) {
            if (is_prime(P) && a_v1 % P != 0 && c_v1 % P != 0) {
                trial_num = trial_num + 1;
                int minus_b = -b_v1;
                while (minus_b < 0) minus_b = minus_b + P;
                resume_solution_v1(solution_v1_pointer_backup);
                int m = get_power_cycle_mod(P, c_v1);
                int d = greatest_common_divisor(m, k);
                if (d > 1) {
                    write_solution_v1(P);
                    if(!assertion) return;
                    write_solution_v1(m);
                    if(!assertion) return;
                    write_solution_v1(m / d);
                    if(!assertion) return;
                    int i = 0;
                    while ( i < m / d) {
                        write_solution_v1((yr % d) + i * d);
                        if(!assertion) return;
                        i = i + 1;
                    }
                    write_solution_v1(m / d);
                    if(!assertion) return;
                    i = 0;
                    while ( i < m / d) {
                        write_solution_v1(power(c_v1, (yr % d) + i * d, P));
                        if(!assertion) return;
                        i = i + 1;
                    }
                    write_solution_v1(P);
                    if(!assertion) return;
                    write_solution_v1(m / d);
                    if(!assertion) return;
                    i = 0;
                    int condition = 1;
                    while ( i < m / d) {
                        write_solution_v1((power(c_v1, (yr % d) + i * d, P) + minus_b) % P);
                        condition = condition && (get_power_position_mod(P, a_v1, (power(c_v1, (yr % d) + i * d, P) + minus_b) % P) == -1);
                        if(!assertion) return;
                        i = i + 1;
                    }
                    write_solution_v1(P);
                    if(!assertion) return;
                    if (condition) {
                        solver_v1_success = 1;
                        return;
                    }
                }
            }
            n = n + 1;
            P = n * k + 1;
        }
        solver_v1_success = 0;
    }
}

void Solve_Diophantine1_II_disproof_C() {
    solver_v1_success = 0;
    if(disable_front_mode) return;
    int M = power(disproof_prime, disproof_power, -1);
    if(!assertion) return;
    int R = (-b_v1) % M;
    while (R < 0) R = R + M;
    // a ^ x = R (mod M)
    write_solution_v1(a_v1);
    if(!assertion) return;
    write_solution_v1(R);
    if(!assertion) return;
    write_solution_v1(M);
    if(!assertion) return;
    int k = get_power_cycle_mod(M, a_v1);
    if(!assertion) return;
    int xr = get_power_position_mod(M, a_v1, R);
    if(!assertion) return;
    // a ^ x = R (mod M) is impossible
    if (xr == -1) {
        write_solution_v1(xr);
        if(!assertion) return;
        solver_v1_success = 1;

    // a ^ x = R (mod M) => x = xr (mod k)
    }else{
        // if (k == 1) return;
        if (k < 10) return;
        write_solution_v1(xr);
        if(!assertion) return;
        write_solution_v1(k);
        if(!assertion) return;
        int solution_v1_pointer_backup = solution_v1_pointer;
        int n = 1, P = n * k + 1;
        int trial_num = 0;
        while (P < mod_threshold_v1 && trial_num < max_trial_num_v1) {
            if (is_prime(P) && a_v1 % P != 0 && c_v1 % P != 0) {
                trial_num = trial_num + 1;
                resume_solution_v1(solution_v1_pointer_backup);
                int m = get_power_cycle_mod(P, a_v1);
                int d = greatest_common_divisor(m, k);
                if (d > 1) {
                    write_solution_v1(P);
                    if(!assertion) return;
                    write_solution_v1(m);
                    if(!assertion) return;
                    write_solution_v1(m / d);
                    if(!assertion) return;
                    int i = 0;
                    while ( i < m / d) {
                        write_solution_v1((xr % d) + i * d);
                        if(!assertion) return;
                        i = i + 1;
                    }
                    write_solution_v1(m / d);
                    if(!assertion) return;
                    i = 0;
                    while ( i < m / d) {
                        write_solution_v1(power(a_v1, (xr % d) + i * d, P));
                        if(!assertion) return;
                        i = i + 1;
                    }
                    write_solution_v1(P);
                    if(!assertion) return;
                    write_solution_v1(m / d);
                    if(!assertion) return;
                    i = 0;
                    int condition = 1;
                    while ( i < m / d) {
                        write_solution_v1((power(a_v1, (xr % d) + i * d, P) + b_v1) % P);
                        condition = condition && (get_power_position_mod(P, c_v1, (power(a_v1, (xr % d) + i * d, P) + b_v1) % P) == -1);
                        if(!assertion) return;
                        i = i + 1;
                    }
                    write_solution_v1(P);
                    if(!assertion) return;
                    if (condition) {
                        solver_v1_success = 1;
                        return;
                    }
                }
            }
            n = n + 1;
            P = n * k + 1;
        }
        solver_v1_success = 0;
    }
}

void insert_disproof_evidence(int prime, int _power, int type) {
    //"[Solver V1] disproof list needs more space!"
    int array1[44] = {91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 100, 105, 115, 112, 114, 111, 111, 102, 32, 108, 105, 115, 116, 32, 110, 101, 101, 100, 115, 32, 109, 111, 114, 101, 32, 115, 112, 97, 99, 101, 33, 10};
    assert(disproof_priorlist_length < 100, array1);
    if(!assertion) return;
    disproof_priorlist_length = disproof_priorlist_length + 1;
    disproof_priorlist_prime[disproof_priorlist_length-1] = prime;
    disproof_priorlist_power[disproof_priorlist_length-1] = _power;
    disproof_priorlist_type[disproof_priorlist_length-1] = type;
    int list_index = disproof_priorlist_length-1;
    int A, B;
    while (list_index >= 1) {
        A = power(disproof_priorlist_prime[list_index-1], disproof_priorlist_power[list_index-1], -1);
        B = power(disproof_priorlist_prime[list_index], disproof_priorlist_power[list_index], -1);
        //"[Solver V1] unknown error encountered in insert_disproof_evidence!"
        int array2[67] = {91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 117, 110, 107, 110, 111, 119, 110, 32, 101, 114, 114, 111, 114, 32, 101, 110, 99, 111, 117, 110, 116, 101, 114, 101, 100, 32, 105, 110, 32, 105, 110, 115, 101, 114, 116, 95, 100, 105, 115, 112, 114, 111, 111, 102, 95, 101, 118, 105, 100, 101, 110, 99, 101, 33, 10};
        assert(A!= B, array2);
        if(!assertion) return;
        if (A > B) {
            int temp;
            temp = disproof_priorlist_prime[list_index-1];
            disproof_priorlist_prime[list_index-1] = disproof_priorlist_prime[list_index];
            disproof_priorlist_prime[list_index] = temp;

            temp = disproof_priorlist_power[list_index-1];
            disproof_priorlist_power[list_index-1] = disproof_priorlist_power[list_index];
            disproof_priorlist_power[list_index] = temp;

            temp = disproof_priorlist_type[list_index-1];
            disproof_priorlist_type[list_index-1] = disproof_priorlist_type[list_index];
            disproof_priorlist_type[list_index] = temp;
        }else{
            break;
        }
        list_index = list_index - 1;
    }
    // 在命令行输出disproof list（调试用）
    if (!verbose) return;
    int index;
    index = 0;
    while (index < 20) {
        putint(disproof_priorlist_prime[index]);
        putch(space);
        index = index + 1;
    }
    print_line(newline);
    index = 0;
    while (index < 20) {
        putint(disproof_priorlist_power[index]);
        putch(space);
        index = index + 1;
    }
    print_line(newline);
    index = 0;
    while (index < 20) {
        putint(disproof_priorlist_type[index]);
        putch(space);
        index = index + 1;
    }
    print_line(newline);
    print_line(newline);
}

void get_disproof_evidence() {
    //"[Solver V1] can't get disproof evidence: list is empty!"
    int array1[56] = {91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 99, 97, 110, 39, 116, 32, 103, 101, 116, 32, 100, 105, 115, 112, 114, 111, 111, 102, 32, 101, 118, 105, 100, 101, 110, 99, 101, 58, 32, 108, 105, 115, 116, 32, 105, 115, 32, 101, 109, 112, 116, 121, 33, 10};
    assert(disproof_priorlist_length, array1);
    if(!assertion) return;
    int list_index = 0;
    while (list_index < disproof_priorlist_length) {
        if (list_index == 0) {
            disproof_prime = disproof_priorlist_prime[list_index];
            disproof_power = disproof_priorlist_power[list_index];
            disproof_type = disproof_priorlist_type[list_index];
        }else{
            disproof_priorlist_prime[list_index-1] = disproof_priorlist_prime[list_index];
            disproof_priorlist_power[list_index-1] = disproof_priorlist_power[list_index];
            disproof_priorlist_type[list_index-1] = disproof_priorlist_type[list_index];
        }
        list_index = list_index + 1;
    }
    disproof_priorlist_length = disproof_priorlist_length - 1;
    disproof_priorlist_prime[disproof_priorlist_length] = 0;
    disproof_priorlist_power[disproof_priorlist_length] = 0;
    disproof_priorlist_type[disproof_priorlist_length] = 0;
    // 在命令行输出disproof list（调试用）
    if (!verbose) return;
    int index;
    index = 0;
    while (index < 20) {
        putint(disproof_priorlist_prime[index]);
        putch(space);
        index = index + 1;
    }
    print_line(newline);
    index = 0;
    while (index < 20) {
        putint(disproof_priorlist_power[index]);
        putch(space);
        index = index + 1;
    }
    print_line(newline);
    index = 0;
    while (index < 20) {
        putint(disproof_priorlist_type[index]);
        putch(space);
        index = index + 1;
    }
    print_line(newline);
    print_line(newline);
}

void Solve_Diophantine1_I_i() {
    solution_v1[0] = solution_v1_length;
    solver_v1_success = 1;
}

void Solve_Diophantine1_I_ii() {
    int N = solution_v1[solution_v1_pointer-1];
    N = get_power_times_over(b_v1, N);
    if(!assertion) return;
    write_solution_v1(N);
    if(!assertion) return;
    int array_pointer = solution_v1_pointer;
    if (N > 1) {
        write_solution_v1(0);
        if(!assertion) return;
        int a = a_v1, b = b_v1, c = c_v1;
        int a0 = a, c0 = c, x = 1, y = 1;
        while (x < N || y < N) {
            if (a + b < c) {
                if (a > search_threshold_v1 / a0) {
                    //"[Solver V1] Runtime Warning: exceeding range of int32!"
                    int array1[55] = {91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 82, 117, 110, 116, 105, 109, 101, 32, 87, 97, 114, 110, 105, 110, 103, 58, 32, 101, 120, 99, 101, 101, 100, 105, 110, 103, 32, 114, 97, 110, 103, 101, 32, 111, 102, 32, 105, 110, 116, 51, 50, 33, 10};
                    print_line(array1);
                    return;
                }
                a = a * a0;
                x = x + 1;
            }else{
                if (a + b == c) {
                    write_solution_v1(x);
                    if(!assertion) return;
                    write_solution_v1(y);
                    if(!assertion) return;
                    solution_v1[array_pointer] = solution_v1[array_pointer] + 1;
                    if (c > search_threshold_v1 / c0) {
                        //"[Solver V1] Runtime Warning: exceeding range of int32!"
                        int array1[55] = {91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 82, 117, 110, 116, 105, 109, 101, 32, 87, 97, 114, 110, 105, 110, 103, 58, 32, 101, 120, 99, 101, 101, 100, 105, 110, 103, 32, 114, 97, 110, 103, 101, 32, 111, 102, 32, 105, 110, 116, 51, 50, 33, 10};
                        print_line(array1);
                        return;
                    }
                    c = c * c0;
                    y = y + 1;
                }else{
                    if (c > search_threshold_v1 / c0) {
                        //"[Solver V1] Runtime Warning: exceeding range of int32!"
                        int array1[55] = {91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 82, 117, 110, 116, 105, 109, 101, 32, 87, 97, 114, 110, 105, 110, 103, 58, 32, 101, 120, 99, 101, 101, 100, 105, 110, 103, 32, 114, 97, 110, 103, 101, 32, 111, 102, 32, 105, 110, 116, 51, 50, 33, 10};
                        print_line(array1);
                        return;
                    }
                    c = c * c0;
                    y = y + 1;
                }
            }
        }
        solution_v1[0] = solution_v1_length;
        solver_v1_success = 1;
    }else{
        // -1表示不用枚举，“x < 1或y < 1”一出来，方程肯定就无解了
        write_solution_v1(-1);
        solution_v1[0] = solution_v1_length;
        solver_v1_success = 1;
    }
}

void Solve_Diophantine1_I_iii() {
    solution_v1[0] = solution_v1_length;
    solver_v1_success = 1;
}

void Solve_Diophantine1_II() {
    //"[Solver V1] unknown error encountered in situation II!"
    int array1[55] = {91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 117, 110, 107, 110, 111, 119, 110, 32, 101, 114, 114, 111, 114, 32, 101, 110, 99, 111, 117, 110, 116, 101, 114, 101, 100, 32, 105, 110, 32, 115, 105, 116, 117, 97, 116, 105, 111, 110, 32, 73, 73, 33, 10};
    int a = a_v1, b = b_v1, c = c_v1;
    int a0 = a, c0 = c, x0 = 0, x = 1, y0 = 0, y = 1;
    while (1) {
        if (a + b < c) {
            if (a > (search_threshold_v1 - b) / a0) break;
            a = a * a0;
            x = x + 1;
        }else{
            if (a + b == c) {
                x0 = x;
                y0 = y;
                if (c > search_threshold_v1 / c0) break;
                c = c * c0;
                y = y + 1;
            }else{
                if (c > search_threshold_v1 / c0) break;
                c = c * c0;
                y = y + 1;
            }
        }
    }
    // 从“反设x >= x0” / “反设y >= y0”开始归谬
    x0 = x0 + 1;
    y0 = y0 + 1;
    int prime_list_index = 0;
    // 希望对所有小于500的a, b, c顺利求解，这里开得稍大一点
    while (prime_list[prime_list_index] < 600) {
        if (c_v1 % prime_list[prime_list_index] == 0) {
            assert(a_v1 % prime_list[prime_list_index] != 0, array1);
            if (!assertion) return;
            insert_disproof_evidence(prime_list[prime_list_index], y0 * get_degree_wrt(prime_list[prime_list_index], c_v1), 2);
        }
        if (a_v1 % prime_list[prime_list_index] == 0) {
            assert(c_v1 % prime_list[prime_list_index] != 0, array1);
            if (!assertion) return;
            insert_disproof_evidence(prime_list[prime_list_index], x0 * get_degree_wrt(prime_list[prime_list_index], a_v1), 1);
        }
        prime_list_index = prime_list_index + 1;
    }
    int solution_v1_pointer_backup = solution_v1_pointer;
    while (disproof_priorlist_length) {
        resume_solution_v1(solution_v1_pointer_backup);
        get_disproof_evidence();
        if(!assertion) return;
        write_solution_v1(disproof_prime);
        if(!assertion) return;
        write_solution_v1(disproof_power);
        if(!assertion) return;
        write_solution_v1(disproof_type);
        if(!assertion) return;
        if (disproof_type == 1) {
            Solve_Diophantine1_II_disproof_A();
            if(!assertion) return;
            if (solver_v1_success) {
                if (disproof_power > 1) {
                    solution_v1_pointer_backup = solution_v1_pointer;
                    write_solution_v1(0);
                    if(!assertion) return;
                    // 归谬完成，枚举x的有限个取值
                    int a = a_v1, c = c_v1, b = b_v1, y = 1, x = 1;
                    int a0 = a, c0 = c;
                    while (x < disproof_power) {
                        if (a + b < c) {
                            a = a * a0;
                            x = x + 1;
                        }else{
                            if (a + b == c) {
                                write_solution_v1(x);
                                if(!assertion) return;
                                write_solution_v1(y);
                                if(!assertion) return;
                                solution_v1[solution_v1_pointer_backup] = solution_v1[solution_v1_pointer_backup]+1;
                                c = c * c0;
                                y = y + 1;
                            }else{
                                c = c * c0;
                                y = y + 1;
                            }
                        }
                    }
                    solution_v1[0] = solution_v1_length;
                    return;
                }else{
                    // -1表示不用枚举
                    write_solution_v1(-1);
                    solution_v1[0] = solution_v1_length;
                    return;
                }
            }
        }else if (disproof_type == 2) {
            Solve_Diophantine1_II_disproof_C();
            if(!assertion) return;
            if (solver_v1_success) {
                if (disproof_power > 1) {
                    solution_v1_pointer_backup = solution_v1_pointer;
                    write_solution_v1(0);
                    if(!assertion) return;
                    // 归谬完成，枚举y的有限个取值
                    int a = a_v1, c = c_v1, b = b_v1, y = 1, x = 1;
                    int a0 = a, c0 = c;
                    while (y < disproof_power) {
                        if (a + b < c) {
                            a = a * a0;
                            x = x + 1;
                        }else{
                            if (a + b == c) {
                                write_solution_v1(x);
                                if(!assertion) return;
                                write_solution_v1(y);
                                if(!assertion) return;
                                solution_v1[solution_v1_pointer_backup] = solution_v1[solution_v1_pointer_backup]+1;
                                c = c * c0;
                                y = y + 1;
                            }else{
                                c = c * c0;
                                y = y + 1;
                            }
                        }
                    }
                    solution_v1[0] = solution_v1_length;
                    return;
                }else{
                    // -1表示不用枚举
                    write_solution_v1(-1);
                    solution_v1[0] = solution_v1_length;
                    return;
                }
            }
        }else{
            assert(0, array1);
            if(!assertion) return;
        }
        if (power(disproof_prime, disproof_power, -1) < mod_threshold_v1 / disproof_prime) {
            insert_disproof_evidence(disproof_prime, disproof_power+1, disproof_type);
            if(!assertion) return;
        }
    }
    solver_v1_success = 0;
}

void Solve_Diophantine1() {
    //"[Solver V1] a, b, c not set, can't solve now!"
    int array1[46] = {91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 97, 44, 32, 98, 44, 32, 99, 32, 110, 111, 116, 32, 115, 101, 116, 44, 32, 99, 97, 110, 39, 116, 32, 115, 111, 108, 118, 101, 32, 110, 111, 119, 33, 10};
    assert(abc_set_status_v1, array1);
    if(!assertion) return;

    solution_v1_pointer = 1;
    solution_v1_length = 1;
    solver_v1_success = 0;
    disproof_priorlist_length = 0;

    write_solution_v1(a_v1);
    if(!assertion) return;
    write_solution_v1(b_v1);
    if(!assertion) return;
    write_solution_v1(c_v1);
    if(!assertion) return;

    // 情况I - i
    int temp = greatest_common_divisor(b_v1, c_v1);
    if(!assertion) return;
    temp = contain_undividable_prime_part(temp, a_v1);
    if(!assertion) return;
    if (temp) {
        write_solution_v1(1);
        if(!assertion) return;
        write_solution_v1(1);
        if(!assertion) return;
        temp = greatest_common_divisor(b_v1, c_v1);
        if(!assertion) return;
        write_solution_v1(temp);
        if(!assertion) return;
        Solve_Diophantine1_I_i();
        return;
    }

    // 情况I - iii
    temp = greatest_common_divisor(a_v1, b_v1);
    if(!assertion) return;
    temp = contain_undividable_prime_part(temp, c_v1);
    if(!assertion) return;
    if (temp) {
        write_solution_v1(1);
        if(!assertion) return;
        write_solution_v1(3);
        if(!assertion) return;
        temp = greatest_common_divisor(a_v1, b_v1);
        if(!assertion) return;
        write_solution_v1(temp);
        if(!assertion) return;
        Solve_Diophantine1_I_iii();
        return;
    }

    // 情况I - ii
    temp = greatest_common_divisor(a_v1, c_v1);
    if(!assertion) return;
    if (temp > 1) {
        write_solution_v1(1);
        if(!assertion) return;
        write_solution_v1(2);
        if(!assertion) return;
        write_solution_v1(temp);
        if(!assertion) return;
        Solve_Diophantine1_I_ii();
        return;
    }

    // 情况II
    write_solution_v1(2);
    if(!assertion) return;
    Solve_Diophantine1_II();
    if(!assertion) return;
    return;
}

void exhaust_solution_v1(int nsolutions_pointer) {
    int a = solution_v1[1];
    int b = solution_v1[2];
    int c = solution_v1[3];
    int nsolutions = solution_v1[nsolutions_pointer];
    if (nsolutions == -1) { 
        //"So %d ^ %s + %d = %d ^ %s is impossible."
        int array16[41] = {83, 111, 32, 37, 100, 32, 94, 32, 37, 115, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 37, 115, 32, 105, 115, 32, 105, 109, 112, 111, 115, 115, 105, 98, 108, 101, 46, 10};
        print_line_with_dsdds(array16, a, x_name_v1, b, c, y_name_v1);
    }else if (nsolutions == 0) {
        //"Further examination shows that %d ^ %s + %d = %d ^ %s is impossible."
        int array1[69] = {70, 117, 114, 116, 104, 101, 114, 32, 101, 120, 97, 109, 105, 110, 97, 116, 105, 111, 110, 32, 115, 104, 111, 119, 115, 32, 116, 104, 97, 116, 32, 37, 100, 32, 94, 32, 37, 115, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 37, 115, 32, 105, 115, 32, 105, 109, 112, 111, 115, 115, 105, 98, 108, 101, 46, 10};
        print_line_with_dsdds(array1, a, x_name_v1, b, c, y_name_v1);
    }else{
        //"Further examination shows that "
        int array1[32] = {70, 117, 114, 116, 104, 101, 114, 32, 101, 120, 97, 109, 105, 110, 97, 116, 105, 111, 110, 32, 115, 104, 111, 119, 115, 32, 116, 104, 97, 116, 32, 0};
        print_word(array1);
        putch(left_parenthesis);
        print_word(x_name_v1);
        putch(comma);
        putch(space);
        print_word(y_name_v1);
        putch(right_parenthesis);
        putch(space);
        putch(equals);
        putch(space);
        int offset = 1;
        while (offset / 2 < nsolutions) {
            if (offset != 1) {
                putch(comma);
                putch(space);
            }
            putch(left_parenthesis);
            putint(solution_v1[nsolutions_pointer+offset]);
            putch(comma);
            putch(space);
            putint(solution_v1[nsolutions_pointer+offset+1]);
            putch(right_parenthesis);
            offset = offset + 2;
        }
        putch(period);
        print_line(newline);
    }
}

void print_solution_v1() {
    //"[Solver V1] solver failed or name not set, can't print solution!"
    int array1[65] = {91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 115, 111, 108, 118, 101, 114, 32, 102, 97, 105, 108, 101, 100, 32, 111, 114, 32, 110, 97, 109, 101, 32, 110, 111, 116, 32, 115, 101, 116, 44, 32, 99, 97, 110, 39, 116, 32, 112, 114, 105, 110, 116, 32, 115, 111, 108, 117, 116, 105, 111, 110, 33, 10};
    assert(solver_v1_success && xy_name_set_status_v1, array1);
    if (!assertion) return;
    if (verbose) {
        int index = 0;
        // while (index < solution_v1[0]) {
        while (index < 50) {
            putint(solution_v1[index]);
            putch(space);
            index = index + 1;
        }
        print_line(newline);
    }
    //"[Solver V1] solution vector format is incorrect for unknown reason!"
    int array2[68] = {91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 115, 111, 108, 117, 116, 105, 111, 110, 32, 118, 101, 99, 116, 111, 114, 32, 102, 111, 114, 109, 97, 116, 32, 105, 115, 32, 105, 110, 99, 111, 114, 114, 101, 99, 116, 32, 102, 111, 114, 32, 117, 110, 107, 110, 111, 119, 110, 32, 114, 101, 97, 115, 111, 110, 33, 10};
    int a = solution_v1[1];
    int b = solution_v1[2];
    int c = solution_v1[3];
    //"For positive integers %s, %s satisfying %d ^ %s + %d = %d ^ %s,"
    int array14[64] = {70, 111, 114, 32, 112, 111, 115, 105, 116, 105, 118, 101, 32, 105, 110, 116, 101, 103, 101, 114, 115, 32, 37, 115, 44, 32, 37, 115, 32, 115, 97, 116, 105, 115, 102, 121, 105, 110, 103, 32, 37, 100, 32, 94, 32, 37, 115, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 37, 115, 44, 10};
    print_line_with_ssdsdds(array14, x_name_v1, y_name_v1, a, x_name_v1, b, c, y_name_v1);
    int i;
    if (solution_v1[4] == 1) {
        if (solution_v1[5] == 1) {
            //"this is impossible, because it implies that %d ^ %s = 0 (mod %d)."
            int array15[66] = {116, 104, 105, 115, 32, 105, 115, 32, 105, 109, 112, 111, 115, 115, 105, 98, 108, 101, 44, 32, 98, 101, 99, 97, 117, 115, 101, 32, 105, 116, 32, 105, 109, 112, 108, 105, 101, 115, 32, 116, 104, 97, 116, 32, 37, 100, 32, 94, 32, 37, 115, 32, 61, 32, 48, 32, 40, 109, 111, 100, 32, 37, 100, 41, 46, 10};
            print_line_with_dsd(array15, a, x_name_v1, solution_v1[6]);
        }else if (solution_v1[5] == 2) {
            //"if %s >= %d and %s >= %d,"
            int array[26] = {105, 102, 32, 37, 115, 32, 62, 61, 32, 37, 100, 32, 97, 110, 100, 32, 37, 115, 32, 62, 61, 32, 37, 100, 44, 10};
            print_line_with_sdsd(array, x_name_v1, solution_v1[7], y_name_v1, solution_v1[7]);
            //"%d = 0 (mod %d), which is impossible."
            int array2[38] = {37, 100, 32, 61, 32, 48, 32, 40, 109, 111, 100, 32, 37, 100, 41, 44, 32, 119, 104, 105, 99, 104, 32, 105, 115, 32, 105, 109, 112, 111, 115, 115, 105, 98, 108, 101, 46, 10};
            print_line_with_dd(array2, b, power(solution_v1[6], solution_v1[7], -1));
            //"Therefore, %s < %d or %s < %d."
            int array3[31] = {84, 104, 101, 114, 101, 102, 111, 114, 101, 44, 32, 37, 115, 32, 60, 32, 37, 100, 32, 111, 114, 32, 37, 115, 32, 60, 32, 37, 100, 46, 10};
            print_line_with_sdsd(array3, x_name_v1, solution_v1[7], y_name_v1, solution_v1[7]);
            int nsolutions_pointer = 8;
            exhaust_solution_v1(nsolutions_pointer);
        }else if (solution_v1[5] == 3) {
            //"this is impossible, because it implies that %d ^ %s = 0 (mod %d)."
            int array15[66] = {116, 104, 105, 115, 32, 105, 115, 32, 105, 109, 112, 111, 115, 115, 105, 98, 108, 101, 44, 32, 98, 101, 99, 97, 117, 115, 101, 32, 105, 116, 32, 105, 109, 112, 108, 105, 101, 115, 32, 116, 104, 97, 116, 32, 37, 100, 32, 94, 32, 37, 115, 32, 61, 32, 48, 32, 40, 109, 111, 100, 32, 37, 100, 41, 46, 10};
            print_line_with_dsd(array15, c, y_name_v1, solution_v1[6]);
        }else {
            assert(0, array2);
            if(!assertion) return;
        }
    }else if (solution_v1[4] == 2) {
        // disproof prime, power and type
        // int dp_prime = solution_v1[5];  (not used)
        int dp_power = solution_v1[6];
        int dp_type = solution_v1[7];
        solution_v1_pointer = 8;
        // Back Mode: Obtain y = yr (mod k) by disproof assumption and search series {n*k + 1} for an appropriate prime number
        if (dp_type == 1) {
            read_solution_v1();
            int R = read_solution_v1();
            int M = read_solution_v1();
            //"if %s >= %d, %d ^ %s = %d (mod %d)."
            int array1[36] = {105, 102, 32, 37, 115, 32, 62, 61, 32, 37, 100, 44, 32, 37, 100, 32, 94, 32, 37, 115, 32, 61, 32, 37, 100, 32, 40, 109, 111, 100, 32, 37, 100, 41, 46, 10};
            print_line_with_sddsdd(array1, x_name_v1, dp_power, c, y_name_v1, R, M);
            int yr = read_solution_v1();
            if (yr == -1) {
                //"However, this is impossible."
                int array10[29] = {72, 111, 119, 101, 118, 101, 114, 44, 32, 116, 104, 105, 115, 32, 105, 115, 32, 105, 109, 112, 111, 115, 115, 105, 98, 108, 101, 46, 10};
                print_line(array10);
                //"Therefore, %s < %d."
                int array9[20] = {84, 104, 101, 114, 101, 102, 111, 114, 101, 44, 32, 37, 115, 32, 60, 32, 37, 100, 46, 10};
                print_line_with_sd(array9, x_name_v1, dp_power);
                exhaust_solution_v1(solution_v1_pointer);
            }else{
                int k = read_solution_v1();
                int P = read_solution_v1();
                int m = read_solution_v1();
                int npossibilities = read_solution_v1();
                //" (mod %d)."
                int array4[11] = {32, 40, 109, 111, 100, 32, 37, 100, 41, 46, 10};
                // k m 不等，x = xr (mod k) 推出多个关于m的可能余数
                if (k != m) {
                    //"So %s = %d (mod %d), "
                    int array2[22] = {83, 111, 32, 37, 115, 32, 61, 32, 37, 100, 32, 40, 109, 111, 100, 32, 37, 100, 41, 44, 32, 10};
                    print_line_with_sdd(array2, y_name_v1, yr, k);
                    //"which implies "
                    int array3[15] = {119, 104, 105, 99, 104, 32, 105, 109, 112, 108, 105, 101, 115, 32, 0};
                    print_word(array3);
                    print_word(y_name_v1);
                    putch(space);
                    putch(equals);
                    putch(space);
                    i = 0;
                    while (i < npossibilities) {
                        if (i) {
                            putch(comma);
                            putch(space);
                        } 
                        putint(read_solution_v1());
                        i = i + 1;
                    }
                    print_line_with_d(array4, m);
                // k m 相等，npossibilities = 1
                }else {
                    //"So %s = %d (mod %d)."
                    int array2[22] = {83, 111, 32, 37, 115, 32, 61, 32, 37, 100, 32, 40, 109, 111, 100, 32, 37, 100, 41, 46, 10};
                    print_line_with_sdd(array2, y_name_v1, yr, k);
                    read_solution_v1();
                }
                read_solution_v1();
                //"Therefore, "
                int array5[12] = {84, 104, 101, 114, 101, 102, 111, 114, 101, 44, 32, 0};
                print_word(array5);
                putint(c);
                putch(space);
                putch(hat);
                putch(space);
                print_word(y_name_v1);
                putch(space);
                putch(equals);
                putch(space);
                i = 0;
                while (i < npossibilities) {
                    if (i) {
                        putch(comma);
                        putch(space);
                    } 
                    putint(read_solution_v1());
                    i = i + 1;
                }
                print_line_with_d(array4, P);
                read_solution_v1();
                read_solution_v1();
                //"So "
                int array7[4] = {83, 111, 32, 0};
                print_word(array7);
                putint(a);
                putch(space);
                putch(hat);
                putch(space);
                print_word(x_name_v1);
                putch(space);
                putch(equals);
                putch(space);
                i = 0;
                while (i < npossibilities) {
                    if (i) {
                        putch(comma);
                        putch(space);
                    } 
                    putint(read_solution_v1());
                    i = i + 1;
                }
                //" (mod %d), but this is impossible."
                int array8[35] = {32, 40, 109, 111, 100, 32, 37, 100, 41, 44, 32, 98, 117, 116, 32, 116, 104, 105, 115, 32, 105, 115, 32, 105, 109, 112, 111, 115, 115, 105, 98, 108, 101, 46, 10};
                print_line_with_d(array8, P);
                //"Therefore, %s < %d."
                int array9[20] = {84, 104, 101, 114, 101, 102, 111, 114, 101, 44, 32, 37, 115, 32, 60, 32, 37, 100, 46, 10};
                print_line_with_sd(array9, x_name_v1, dp_power);
                read_solution_v1();
                exhaust_solution_v1(solution_v1_pointer);
            }
        // Front Mode: Obtain x = xr (mod k) by disproof assumption and search series {n*k + 1} for an appropriate prime number
        }else if (dp_type == 2){
            read_solution_v1();
            int R = read_solution_v1();
            int M = read_solution_v1();
            //"if %s >= %d, %d ^ %s = %d (mod %d)."
            int array1[36] = {105, 102, 32, 37, 115, 32, 62, 61, 32, 37, 100, 44, 32, 37, 100, 32, 94, 32, 37, 115, 32, 61, 32, 37, 100, 32, 40, 109, 111, 100, 32, 37, 100, 41, 46, 10};
            print_line_with_sddsdd(array1, y_name_v1, dp_power, a, x_name_v1, R, M);
            int xr = read_solution_v1();
            if (xr == -1) {
                //"However, this is impossible."
                int array10[29] = {72, 111, 119, 101, 118, 101, 114, 44, 32, 116, 104, 105, 115, 32, 105, 115, 32, 105, 109, 112, 111, 115, 115, 105, 98, 108, 101, 46, 10};
                print_line(array10);
                //"Therefore, %s < %d."
                int array9[20] = {84, 104, 101, 114, 101, 102, 111, 114, 101, 44, 32, 37, 115, 32, 60, 32, 37, 100, 46, 10};
                print_line_with_sd(array9, y_name_v1, dp_power);
                exhaust_solution_v1(solution_v1_pointer);
            }else{
                int k = read_solution_v1();
                int P = read_solution_v1();
                int m = read_solution_v1();
                int npossibilities = read_solution_v1();
                //" (mod %d)."
                int array4[11] = {32, 40, 109, 111, 100, 32, 37, 100, 41, 46, 10};
                // k m 不等，x = xr (mod k) 推出多个关于m的可能余数
                if (k != m) {
                    //"So %s = %d (mod %d), "
                    int array2[22] = {83, 111, 32, 37, 115, 32, 61, 32, 37, 100, 32, 40, 109, 111, 100, 32, 37, 100, 41, 44, 32, 10};
                    print_line_with_sdd(array2, x_name_v1, xr, k);
                    //"which implies "
                    int array3[15] = {119, 104, 105, 99, 104, 32, 105, 109, 112, 108, 105, 101, 115, 32, 0};
                    print_word(array3);
                    print_word(x_name_v1);
                    putch(space);
                    putch(equals);
                    putch(space);
                    i = 0;
                    while (i < npossibilities) {
                        if (i) {
                            putch(comma);
                            putch(space);
                        } 
                        putint(read_solution_v1());
                        i = i + 1;
                    }
                    print_line_with_d(array4, m);
                // k m 相等，npossibilities = 1
                }else {
                    //"So %s = %d (mod %d)."
                    int array2[22] = {83, 111, 32, 37, 115, 32, 61, 32, 37, 100, 32, 40, 109, 111, 100, 32, 37, 100, 41, 46, 10};
                    print_line_with_sdd(array2, x_name_v1, xr, k);
                    read_solution_v1();
                }
                read_solution_v1();
                //"Therefore, "
                int array5[12] = {84, 104, 101, 114, 101, 102, 111, 114, 101, 44, 32, 0};
                print_word(array5);
                putint(a);
                putch(space);
                putch(hat);
                putch(space);
                print_word(x_name_v1);
                putch(space);
                putch(equals);
                putch(space);
                i = 0;
                while (i < npossibilities) {
                    if (i) {
                        putch(comma);
                        putch(space);
                    } 
                    putint(read_solution_v1());
                    i = i + 1;
                }
                print_line_with_d(array4, P);
                read_solution_v1();
                read_solution_v1();
                //"So "
                int array7[4] = {83, 111, 32, 0};
                print_word(array7);
                putint(c);
                putch(space);
                putch(hat);
                putch(space);
                print_word(y_name_v1);
                putch(space);
                putch(equals);
                putch(space);
                i = 0;
                while (i < npossibilities) {
                    if (i) {
                        putch(comma);
                        putch(space);
                    } 
                    putint(read_solution_v1());
                    i = i + 1;
                }
                //" (mod %d), but this is impossible."
                int array8[35] = {32, 40, 109, 111, 100, 32, 37, 100, 41, 44, 32, 98, 117, 116, 32, 116, 104, 105, 115, 32, 105, 115, 32, 105, 109, 112, 111, 115, 115, 105, 98, 108, 101, 46, 10};
                print_line_with_d(array8, P);
                //"Therefore, %s < %d."
                int array9[20] = {84, 104, 101, 114, 101, 102, 111, 114, 101, 44, 32, 37, 115, 32, 60, 32, 37, 100, 46, 10};
                print_line_with_sd(array9, y_name_v1, dp_power);
                read_solution_v1();
                exhaust_solution_v1(solution_v1_pointer);
            }
        }else{
            assert(0, array2);
            if(!assertion) return;
        }
    }else{
        assert(0, array2);
        if(!assertion) return;
    }
}

void Solve_Diophantine1_interface() {
    //"Now solving diophantine equation a^x + b = c^y for its positive integer solutions (x,y)."
    int array17[89] = {78, 111, 119, 32, 115, 111, 108, 118, 105, 110, 103, 32, 100, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 32, 101, 113, 117, 97, 116, 105, 111, 110, 32, 97, 94, 120, 32, 43, 32, 98, 32, 61, 32, 99, 94, 121, 32, 102, 111, 114, 32, 105, 116, 115, 32, 112, 111, 115, 105, 116, 105, 118, 101, 32, 105, 110, 116, 101, 103, 101, 114, 32, 115, 111, 108, 117, 116, 105, 111, 110, 115, 32, 40, 120, 44, 121, 41, 46, 10};
    print_line(array17);
    //"Please input a (a should be a positive integer >= 2):"
    int array11[54] = {80, 108, 101, 97, 115, 101, 32, 105, 110, 112, 117, 116, 32, 97, 32, 40, 97, 32, 115, 104, 111, 117, 108, 100, 32, 98, 101, 32, 97, 32, 112, 111, 115, 105, 116, 105, 118, 101, 32, 105, 110, 116, 101, 103, 101, 114, 32, 62, 61, 32, 50, 41, 58, 10};
    print_line(array11);
    int a = getint();
    //"Please input b (b should be a positive integer):"
    int array13[49] = {80, 108, 101, 97, 115, 101, 32, 105, 110, 112, 117, 116, 32, 98, 32, 40, 98, 32, 115, 104, 111, 117, 108, 100, 32, 98, 101, 32, 97, 32, 112, 111, 115, 105, 116, 105, 118, 101, 32, 105, 110, 116, 101, 103, 101, 114, 41, 58, 10};
    print_line(array13);
    int b = getint();
    //"Please input c (c should be a positive integer >= 2):"
    int array12[54] = {80, 108, 101, 97, 115, 101, 32, 105, 110, 112, 117, 116, 32, 99, 32, 40, 99, 32, 115, 104, 111, 117, 108, 100, 32, 98, 101, 32, 97, 32, 112, 111, 115, 105, 116, 105, 118, 101, 32, 105, 110, 116, 101, 103, 101, 114, 32, 62, 61, 32, 50, 41, 58, 10};
    print_line(array12);
    int c = getint();
    set_abc_v1(a, b, c);
    if(!assertion) return;
    set_xy_name_v1(string_x, string_y, strlen_x, strlen_y);
    // set_xy_name_v1(string_u, string_v, strlen_u, strlen_v);
    if(!assertion) return;
    Solve_Diophantine1();
    if(!assertion) return;
    if (solver_v1_success) {
        print_solution_v1();
        if(!assertion) return;
    }else{
        //"[Solver V1] solver failed!"
        int array1[27] = {91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 115, 111, 108, 118, 101, 114, 32, 102, 97, 105, 108, 101, 100, 33, 10};
        print_line(array1);
    }
    return;
}

void Solve_Diophantine1_test_range(int a_max, int b_max, int c_max) {
    int a = 2;
    int first_time_protection = 1;
    while (a <= a_max) {
        int b = 1;
        while (b <= b_max) {
            int c = 2;
            while (c <= c_max) {
                set_abc_v1(a, b, c);
                Solve_Diophantine1();
                if (first_time_protection) {
                    first_time_protection = 0;
                }else{
                    print_line(newline);
                }
                print_solution_v1();
                if(!assertion) {
                    getint();
                }
                c = c + 1;
            }
            b = b + 1;
        }
        a = a + 1;
    }
}

int main() {
    Solve_Diophantine1_interface();
}