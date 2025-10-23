/*
 * 第一代自动机 Solver V1        by parkcai
 * 
 * 【用途】
 * 全自动地求解形如a ^ x + b = c ^ y的关于正整数x, y的不定方程
 * 其中，a, b, c已知且满足a >= 2, b >= 1, c >= 2
 * 
 * 【有效求解范围】
 * 经过测试，第一代自动机可以正确而迅速地求解2 <= a <= 70, 2 <= b <= 30, 2 <= c <= 70
 * 范围内的所有方程。在此范围之外，求解有可能失败，但也有很大概率成功。
 * 譬如，方程2 ^ x + 89 = 91 ^ y是可以顺利求解的。
 * 导致求解失败的原因：
 * 1. prime_list短了（见prime_list.h）
 * 2. search_threshold/mod_threshold/max_trial_num调得太低
 * （mod_threshold/max_trial_num调得太高是不好的，因为自动机会尝试很多种求解方案，
 * 如果这两个参数调得太高，会在前几个失败的方案上浪费过多时间）
 * 作者相信，在数学意义上，此程序所给出的算法可以解出所有的a ^ x + b = c ^ y
 */
   

// ------------------------------ SysY utils section ------------------------------

const int endl = 10;
const int space = 32;
const int left_parenthesis = 40;
const int right_parenthesis = 41;
const int comma = 44;
const int hyphen = 45;
const int period = 46;
const int slash = 47;
const int percentage = 37;
const int equals = 61;
const int backslash = 92;
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
int string_w[2] = {119, 0};
int strlen_w = 2;
int assertion = 1;

// ------------------------------ SysY printf section ------------------------------

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


void assert(int expr, int err_info[]) {
    assertion = expr;
    if (!assertion) {
        print_line(err_info);
    }
}

        
void print_line_with_d(int line[], int arg1) {
    if (!line[0]) return;
    int i = 0;
    int count = 1;
    while (line[i] != endl) {
        if (line[i] != percentage) {
            if (line[i] != backslash) {
                putch(line[i]);
                i = i + 1;
            }else{
                putch(line[i+1]);
                i = i + 2;
            }
        }else{
            if (count == 1) {
                putint(arg1);
            }
            i = i + 2;
            count = count + 1;
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
            if (line[i] != backslash) {
                putch(line[i]);
                i = i + 1;
            }else{
                putch(line[i+1]);
                i = i + 2;
            }
        }else{
            if (count == 1) {
                putint(arg1);
            }
            else if (count == 2) {
                putint(arg2);
            }
            i = i + 2;
            count = count + 1;
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
            if (line[i] != backslash) {
                putch(line[i]);
                i = i + 1;
            }else{
                putch(line[i+1]);
                i = i + 2;
            }
        }else{
            if (count == 1) {
                print_word(arg1);
            }
            else if (count == 2) {
                putint(arg2);
            }
            i = i + 2;
            count = count + 1;
        }
    }
    putch(endl);
}

        
void print_line_with_ddd(int line[], int arg1, int arg2, int arg3) {
    if (!line[0]) return;
    int i = 0;
    int count = 1;
    while (line[i] != endl) {
        if (line[i] != percentage) {
            if (line[i] != backslash) {
                putch(line[i]);
                i = i + 1;
            }else{
                putch(line[i+1]);
                i = i + 2;
            }
        }else{
            if (count == 1) {
                putint(arg1);
            }
            else if (count == 2) {
                putint(arg2);
            }
            else if (count == 3) {
                putint(arg3);
            }
            i = i + 2;
            count = count + 1;
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
            if (line[i] != backslash) {
                putch(line[i]);
                i = i + 1;
            }else{
                putch(line[i+1]);
                i = i + 2;
            }
        }else{
            if (count == 1) {
                putint(arg1);
            }
            else if (count == 2) {
                print_word(arg2);
            }
            else if (count == 3) {
                putint(arg3);
            }
            i = i + 2;
            count = count + 1;
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
            if (line[i] != backslash) {
                putch(line[i]);
                i = i + 1;
            }else{
                putch(line[i+1]);
                i = i + 2;
            }
        }else{
            if (count == 1) {
                print_word(arg1);
            }
            else if (count == 2) {
                putint(arg2);
            }
            else if (count == 3) {
                putint(arg3);
            }
            i = i + 2;
            count = count + 1;
        }
    }
    putch(endl);
}

        
void print_line_with_dddd(int line[], int arg1, int arg2, int arg3, int arg4) {
    if (!line[0]) return;
    int i = 0;
    int count = 1;
    while (line[i] != endl) {
        if (line[i] != percentage) {
            if (line[i] != backslash) {
                putch(line[i]);
                i = i + 1;
            }else{
                putch(line[i+1]);
                i = i + 2;
            }
        }else{
            if (count == 1) {
                putint(arg1);
            }
            else if (count == 2) {
                putint(arg2);
            }
            else if (count == 3) {
                putint(arg3);
            }
            else if (count == 4) {
                putint(arg4);
            }
            i = i + 2;
            count = count + 1;
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
            if (line[i] != backslash) {
                putch(line[i]);
                i = i + 1;
            }else{
                putch(line[i+1]);
                i = i + 2;
            }
        }else{
            if (count == 1) {
                print_word(arg1);
            }
            else if (count == 2) {
                putint(arg2);
            }
            else if (count == 3) {
                print_word(arg3);
            }
            else if (count == 4) {
                putint(arg4);
            }
            i = i + 2;
            count = count + 1;
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
            if (line[i] != backslash) {
                putch(line[i]);
                i = i + 1;
            }else{
                putch(line[i+1]);
                i = i + 2;
            }
        }else{
            if (count == 1) {
                putint(arg1);
            }
            else if (count == 2) {
                print_word(arg2);
            }
            else if (count == 3) {
                putint(arg3);
            }
            else if (count == 4) {
                putint(arg4);
            }
            else if (count == 5) {
                print_word(arg5);
            }
            i = i + 2;
            count = count + 1;
        }
    }
    putch(endl);
}

        
void print_line_with_dddddd(int line[], int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    if (!line[0]) return;
    int i = 0;
    int count = 1;
    while (line[i] != endl) {
        if (line[i] != percentage) {
            if (line[i] != backslash) {
                putch(line[i]);
                i = i + 1;
            }else{
                putch(line[i+1]);
                i = i + 2;
            }
        }else{
            if (count == 1) {
                putint(arg1);
            }
            else if (count == 2) {
                putint(arg2);
            }
            else if (count == 3) {
                putint(arg3);
            }
            else if (count == 4) {
                putint(arg4);
            }
            else if (count == 5) {
                putint(arg5);
            }
            else if (count == 6) {
                putint(arg6);
            }
            i = i + 2;
            count = count + 1;
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
            if (line[i] != backslash) {
                putch(line[i]);
                i = i + 1;
            }else{
                putch(line[i+1]);
                i = i + 2;
            }
        }else{
            if (count == 1) {
                print_word(arg1);
            }
            else if (count == 2) {
                putint(arg2);
            }
            else if (count == 3) {
                putint(arg3);
            }
            else if (count == 4) {
                print_word(arg4);
            }
            else if (count == 5) {
                putint(arg5);
            }
            else if (count == 6) {
                putint(arg6);
            }
            i = i + 2;
            count = count + 1;
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
            if (line[i] != backslash) {
                putch(line[i]);
                i = i + 1;
            }else{
                putch(line[i+1]);
                i = i + 2;
            }
        }else{
            if (count == 1) {
                print_word(arg1);
            }
            else if (count == 2) {
                print_word(arg2);
            }
            else if (count == 3) {
                putint(arg3);
            }
            else if (count == 4) {
                print_word(arg4);
            }
            else if (count == 5) {
                putint(arg5);
            }
            else if (count == 6) {
                putint(arg6);
            }
            else if (count == 7) {
                print_word(arg7);
            }
            i = i + 2;
            count = count + 1;
        }
    }
    putch(endl);
}

// ------------------------------ arithmetic section ------------------------------

int greatest_common_divisor(int n, int m) {
    // "Invalid input of greatest_common_divisor!"
    int array_qahftr[42] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 103, 114, 101, 97, 116, 101, 115, 116, 95, 99, 111, 109, 109, 111, 110, 95, 100, 105, 118, 105, 115, 111, 114, 33, 10};
    assert(n >= 1 && m >= 1, array_qahftr);
    if (!assertion) return 0;
    int temp;
    while (m != 0) {
        temp = m;
        m = n % m;
        n = temp;
    }
    return n;
}


int least_common_multiple(int n, int m) {
    // "Invalid input of least_common_multiple!"
    int array_xckafn[40] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 108, 101, 97, 115, 116, 95, 99, 111, 109, 109, 111, 110, 95, 109, 117, 108, 116, 105, 112, 108, 101, 33, 10};
    assert(n >= 1 && m >= 1, array_xckafn);
    if (!assertion) return 0;
    int d = greatest_common_divisor(n, m);
    int res;
    int RES; /* toy version big int declaration */
    RES = m / d; /* toy version big int assignment */
    RES = RES * n; /* toy version big int operation */
    res = RES; /* toy version big int export */
    /* toy version big int resource release of RES (do nothing) */
    return res;
}


int get_power_cycle_mod(int n, int m) {
    // "Invalid input of get_power_cycle_mod!"
    int array_afqofp[38] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 103, 101, 116, 95, 112, 111, 119, 101, 114, 95, 99, 121, 99, 108, 101, 95, 109, 111, 100, 33, 10};
    assert(n >= 2 && m >= 1, array_afqofp);
    if (!assertion) return 0;
    // "Invalid input of get_power_cycle_mod!"
    int array_vausie[38] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 103, 101, 116, 95, 112, 111, 119, 101, 114, 95, 99, 121, 99, 108, 101, 95, 109, 111, 100, 33, 10};
    assert(greatest_common_divisor(n,m) == 1, array_vausie);
    if (!assertion) return 0;
    m = m % n; if (m == 1) return 1;
    int result = 1;
    int M; /* toy version big int declaration */
    M = m; /* toy version big int assignment */
    while ((M != 1) /* toy version big int comparison */ ) {
        M = M * m; /* toy version big int operation */
        M = M % n; /* toy version big int operation */
        result = result + 1;
    }
    /* toy version big int resource release of M (do nothing) */
    return result;
}


int get_power_position_mod(int n, int m, int k) {
    // "Invalid input of get_power_position_mod!"
    int array_yiccwp[41] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 103, 101, 116, 95, 112, 111, 119, 101, 114, 95, 112, 111, 115, 105, 116, 105, 111, 110, 95, 109, 111, 100, 33, 10};
    assert(n >= 2 && m >= 1 && k >= 0, array_yiccwp);
    if (!assertion) return 0;
    // "Invalid input of get_power_position_mod!"
    int array_usnzjo[41] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 103, 101, 116, 95, 112, 111, 119, 101, 114, 95, 112, 111, 115, 105, 116, 105, 111, 110, 95, 109, 111, 100, 33, 10};
    assert(greatest_common_divisor(n,m) == 1, array_usnzjo);
    if (!assertion) return 0;    
    k = k % n; if (k == 1) return 0;
    m = m % n;
    int result = 1;
    int M; /* toy version big int declaration */
    M = m; /* toy version big int assignment */
    while ((M != 1) /* toy version big int comparison */ ) {
        if ((M == k) /* toy version big int comparison */ ) {
            /* toy version big int resource release of M (do nothing) */
            return result;
        }
        M = M * m; /* toy version big int operation */
        M = M % n; /* toy version big int operation */
        result = result + 1;
    }
    /* toy version big int resource release of M (do nothing) */
    return -1;
}


int is_prime(int n) {
    // "Invalid input of is_prime!"
    int array_vqwpsb[27] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 105, 115, 95, 112, 114, 105, 109, 101, 33, 10};
    assert(n >= 1, array_vqwpsb);
    if (!assertion) return 0;
    if (n == 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    int i = 5;
    int TMP; /* toy version big int declaration */
    while (1) {
        TMP = i; /* toy version big int assignment */
        TMP = TMP * TMP; /* toy version big int operation */
        if ((TMP > n /* toy version big int comparison */ )) break;
        if (n % i == 0 || n % (i + 2) == 0) {
            /* toy version big int resource release of TMP (do nothing) */
            return 0; 
        }
        i = i + 6;
    }
    /* toy version big int resource release of TMP (do nothing) */
    return 1; 
}


int power(int base, int exp, int mod) {
    // "Invalid input of power!"
    int array_fhcgch[24] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 112, 111, 119, 101, 114, 33, 10};
    assert(base >= 1 && exp >= 0 && (mod >= 2 || mod == -1), array_fhcgch);
    if (!assertion) return 0;
    int i = 0, res;
    int RES; /* toy version big int declaration */
    RES = 1; /* toy version big int assignment */
    while (i < exp) {
        RES = RES * base; /* toy version big int operation */
        if (mod != -1) {
            RES = RES % mod; /* toy version big int operation */
        }
        i = i + 1;
    }
    res = RES; /* toy version big int export */
    /* toy version big int resource release of RES (do nothing) */
    return res;
}


int contain_undividable_prime_part(int d, int x) {
    // "Invalid input of contain_undividable_prime_part!"
    int array_qjjfgy[49] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 99, 111, 110, 116, 97, 105, 110, 95, 117, 110, 100, 105, 118, 105, 100, 97, 98, 108, 101, 95, 112, 114, 105, 109, 101, 95, 112, 97, 114, 116, 33, 10};
    assert(d >= 1 && x >= 1, array_qjjfgy);
    if (!assertion) return 0;
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
    // "Invalid input of get_power_times_over!"
    int array_qpesej[39] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 103, 101, 116, 95, 112, 111, 119, 101, 114, 95, 116, 105, 109, 101, 115, 95, 111, 118, 101, 114, 33, 10};
    assert(a >= 2 && M >= 1, array_qpesej);
    if (!assertion) return 0;
    int n = 1;
    int A; /* toy version big int declaration */
    A = a; /* toy version big int assignment */
    while ((A <= M /* toy version big int comparison */ )) {
        A = A * a; /* toy version big int operation */
        n = n + 1;
    }
    /* toy version big int resource release of A (do nothing) */
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


int is_power_of(int a, int b) {
    if (a == 0) {
        return (b == 0) || (b == 1);
    }else if (a == 1) {
        return b == 1;
    }else if (a >= 2) {
        if (b <= 0) return 0;
        int n = get_power_times_over(b, a) - 1;
        return power(a, n, -1) == b;
    }else{
        if (!b) return 0;
        int abs_a = -a;
        int abs_b = b;
        if (b < 0) abs_b = -b;
        int n = get_power_times_over(abs_b, abs_a) - 1;
        return power(abs_a, n, -1) == abs_b && ((b > 0 && n % 2 == 0) || (b < 0 && n % 2));
    }
}


int get_value_mod(int M, int N) {
    while (N < 0) N = N + M;
    return N % M;
}

// ------------------------------ prime list section ------------------------------

const int prime_list[430] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511, 1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, 1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741, 1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811, 1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889, 1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987, 1993, 1997, 1999, 2003, 2011, 2017, 2027, 2029, 2039, 2053, 2063, 2069, 2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129, 2131, 2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207, 2213, 2221, 2237, 2239, 2243, 2251, 2267, 2269, 2273, 2281, 2287, 2293, 2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357, 2371, 2377, 2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423, 2437, 2441, 2447, 2459, 2467, 2473, 2477, 2503, 2521, 2531, 2539, 2543, 2549, 2551, 2557, 2579, 2591, 2593, 2609, 2617, 2621, 2633, 2647, 2657, 2659, 2663, 2671, 2677, 2683, 2687, 2689, 2693, 2699, 2707, 2711, 2713, 2719, 2729, 2731, 2741, 2749, 2753, 2767, 2777, 2789, 2791, 2797, 2801, 2803, 2819, 2833, 2837, 2843, 2851, 2857, 2861, 2879, 2887, 2897, 2903, 2909, 2917, 2927, 2939, 2953, 2957, 2963, 2969, 2971, 2999};

// ------------------------------ solver v1 section ------------------------------

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
int solution_max_length_v1 = 200000;
int solver_v1_success = 0;
int int_threshold = 2100000000;
// 这两个设小了可能会导致求解失败
// 设大了可能导致那些需要多试几个方案的方程在一个方案上耗费的时间过长
int mod_threshold_v1 = 1000000000;
int max_trial_num_v1 = 25;
int max_trial_num_v1_backup;
int mod_threshold_v1_backup;
int disproof_priorlist_prime[100];
int disproof_priorlist_power[100];
int disproof_priorlist_type[100]; // a = 1, c = 3
int disproof_prime;
int disproof_power;
int disproof_type;
int disproof_priorlist_length = 0;
int verbose_v1 = 1;
int disable_front_mode = 0;
int disable_back_mode = 0;
int hijack_settings = 0;


void set_abc_v1(int a, int b, int c) {
    // "Invalid input of set_abc_v1!"
    int array_qkznyc[29] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 115, 101, 116, 95, 97, 98, 99, 95, 118, 49, 33, 10};
    assert(a >= 2 && c >= 2 && b >= 1, array_qkznyc);
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
    // "Invalid input of set_xy_name_v1!"
    int array_zezgcl[33] = {73, 110, 118, 97, 108, 105, 100, 32, 105, 110, 112, 117, 116, 32, 111, 102, 32, 115, 101, 116, 95, 120, 121, 95, 110, 97, 109, 101, 95, 118, 49, 33, 10};
    assert(x_encounter_zero && y_encounter_zero, array_zezgcl);
    if (!assertion) return;
    xy_name_set_status_v1 = 1;
}


void write_solution_v1(int x) {
    // "-- [Solver V1] solution pointer out of legal range!"
    int array_sipnko[52] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 115, 111, 108, 117, 116, 105, 111, 110, 32, 112, 111, 105, 110, 116, 101, 114, 32, 111, 117, 116, 32, 111, 102, 32, 108, 101, 103, 97, 108, 32, 114, 97, 110, 103, 101, 33, 10};
    assert(solution_v1_pointer >= 0 && solution_v1_pointer < solution_max_length_v1, array_sipnko);
    if (!assertion) return;
    solution_v1[solution_v1_pointer] = x;
    solution_v1_pointer = solution_v1_pointer + 1;
    solution_v1_length = solution_v1_length + 1;
    solution_v1[0] = solution_v1_length;
}


int read_solution_v1() {
    // "-- [Solver V1] solution pointer out of legal range!"
    int array_gsayns[52] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 115, 111, 108, 117, 116, 105, 111, 110, 32, 112, 111, 105, 110, 116, 101, 114, 32, 111, 117, 116, 32, 111, 102, 32, 108, 101, 103, 97, 108, 32, 114, 97, 110, 103, 101, 33, 10};
    assert(solution_v1_pointer >= 0 && solution_v1_pointer < solution_max_length_v1, array_gsayns);
    if (!assertion) return 0;
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
                if (verbose_v1) {
                    // "-- Trying prime %d..."
                    int string_trjbri[22] = {45, 45, 32, 84, 114, 121, 105, 110, 103, 32, 112, 114, 105, 109, 101, 32, 37, 100, 46, 46, 46, 10};
                    print_line_with_d(string_trjbri, P);
                }
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
                    while (i < m / d) {
                        write_solution_v1((yr % d) + i * d);
                        if(!assertion) return;
                        i = i + 1;
                    }
                    write_solution_v1(m / d);
                    if(!assertion) return;
                    i = 0;
                    while (i < m / d) {
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
                if (verbose_v1) {
                    // "-- Trying prime %d..."
                    int string_iwshik[22] = {45, 45, 32, 84, 114, 121, 105, 110, 103, 32, 112, 114, 105, 109, 101, 32, 37, 100, 46, 46, 46, 10};
                    print_line_with_d(string_iwshik, P);
                }
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
                    while (i < m / d) {
                        write_solution_v1((xr % d) + i * d);
                        if(!assertion) return;
                        i = i + 1;
                    }
                    write_solution_v1(m / d);
                    if(!assertion) return;
                    i = 0;
                    while (i < m / d) {
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
                    while (i < m / d) {
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
// "-- [Solver V1] disproof list needs more space!"
    int array_khdkyr[47] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 100, 105, 115, 112, 114, 111, 111, 102, 32, 108, 105, 115, 116, 32, 110, 101, 101, 100, 115, 32, 109, 111, 114, 101, 32, 115, 112, 97, 99, 101, 33, 10};
    assert(disproof_priorlist_length < 100, array_khdkyr);
    if (!assertion) return;
    disproof_priorlist_length = disproof_priorlist_length + 1;
    disproof_priorlist_prime[disproof_priorlist_length-1] = prime;
    disproof_priorlist_power[disproof_priorlist_length-1] = _power;
    disproof_priorlist_type[disproof_priorlist_length-1] = type;
    int list_index = disproof_priorlist_length-1;
    int A, B;
    while (list_index >= 1) {
        A = power(disproof_priorlist_prime[list_index-1], disproof_priorlist_power[list_index-1], -1);
        B = power(disproof_priorlist_prime[list_index], disproof_priorlist_power[list_index], -1);
        // "-- [Solver V1] unknown error encountered in insert_disproof_evidence!"
        int array_xqhoah[70] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 117, 110, 107, 110, 111, 119, 110, 32, 101, 114, 114, 111, 114, 32, 101, 110, 99, 111, 117, 110, 116, 101, 114, 101, 100, 32, 105, 110, 32, 105, 110, 115, 101, 114, 116, 95, 100, 105, 115, 112, 114, 111, 111, 102, 95, 101, 118, 105, 100, 101, 110, 99, 101, 33, 10};
        assert(A!= B, array_xqhoah);
        if (!assertion) return;
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
}


void get_disproof_evidence() {
    // "-- [Solver V1] can't get disproof evidence: list is empty!"
    int array_lprmlf[59] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 99, 97, 110, 39, 116, 32, 103, 101, 116, 32, 100, 105, 115, 112, 114, 111, 111, 102, 32, 101, 118, 105, 100, 101, 110, 99, 101, 58, 32, 108, 105, 115, 116, 32, 105, 115, 32, 101, 109, 112, 116, 121, 33, 10};
    assert(disproof_priorlist_length, array_lprmlf);
    if (!assertion) return;
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
}


int special_as[40] = {31, 31, 31, 43, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 59, 59, 59, 59, 59, 59, 59, 59, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83, 83};
int special_bs[40] = {2, 4, 4, 21, 49, 81, 81, 84, 84, 84, 84, 91, 96, 97, 31, 42, 42, 42, 73, 85, 87, 99, 7, 11, 18, 21, 29, 30, 33, 33, 40, 51, 61, 78, 84, 84, 85, 93, 94, 95};
int special_cs[40] = {47, 47, 53, 59, 59, 73, 83, 19, 59, 83, 89, 31, 59, 59, 47, 67, 83, 89, 47, 83, 47, 47, 59, 59, 19, 59, 59, 59, 47, 89, 59, 59, 59, 59, 59, 89, 47, 89, 59, 59};
int special_xs[40] = {25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 10, 25, 25, 25, 25, 25, 25, 25, 10, 25, 25, 10, 25, 25, 25, 25, 25, 50, 25, 10, 10};
int special_ys[40] = {1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000, 1000000000};

void tune_settings(int a, int b, int c) {
    if (hijack_settings) return;
    max_trial_num_v1_backup = max_trial_num_v1;
    mod_threshold_v1_backup = mod_threshold_v1;

    // 点状设置（优先生效）
    int i = 0;
    while (i < 40) {
        if (a == special_as[i] && b == special_bs[i] && c == special_cs[i]) {
            max_trial_num_v1 = special_xs[i]; mod_threshold_v1 = special_ys[i]; return;
        }
        i = i + 1;
    }
    
    // 面状设置
    if (a <= 125 && b <= 125 && c <= 125) {
        max_trial_num_v1 = 5; mod_threshold_v1 = 1000000000;
        return;
    }
    if (a <= 250 && b <= 250 && c <= 250) {
        max_trial_num_v1 = 25; mod_threshold_v1 = 1000000000;
        return;
    }
    if (a <= 500 && b <= 500 && c <= 500) {
        max_trial_num_v1 = 15; mod_threshold_v1 = 50000000;
        return;
    }
}


void recover_settings() {
    if (hijack_settings) return;
    max_trial_num_v1 = max_trial_num_v1_backup;
    mod_threshold_v1 = mod_threshold_v1_backup;
}


void Solve_Diophantine1_I_i() {
    solution_v1[0] = solution_v1_length;
    solver_v1_success = 1;
}


void Solve_Diophantine1_I_ii() {
    solution_v1[0] = solution_v1_length;
    solver_v1_success = 1;
}


void Solve_Diophantine1_I_iii() {
    int N = solution_v1[solution_v1_pointer-1];
    N = get_power_times_over(b_v1, N);
    if(!assertion) return;
    write_solution_v1(N);
    if(!assertion) return;
    int array_pointer = solution_v1_pointer;
    if (N > 1) {
        write_solution_v1(0);
        if(!assertion) return;
        int A; /* toy version big int declaration */
        int B; /* toy version big int declaration */
        int C; /* toy version big int declaration */
        int TMP; /* toy version big int declaration */
        A = a_v1; /* toy version big int assignment */
        B = b_v1; /* toy version big int assignment */
        C = c_v1; /* toy version big int assignment */
        int a0 = a_v1, c0 = c_v1, x = 1, y = 1;
        while (x < N || y < N) {
            TMP = A + B; /* toy version big int operation */
            TMP = C - TMP; /* toy version big int operation */
            if ((TMP > 0 /* toy version big int comparison */ )) {
                if (A > int_threshold / a0) {
                    // "-- [Solver V1] Runtime Warning: exceeding range of int32; try the non-toy version to solve this case!"
                    int string_mxuecn[102] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 82, 117, 110, 116, 105, 109, 101, 32, 87, 97, 114, 110, 105, 110, 103, 58, 32, 101, 120, 99, 101, 101, 100, 105, 110, 103, 32, 114, 97, 110, 103, 101, 32, 111, 102, 32, 105, 110, 116, 51, 50, 59, 32, 116, 114, 121, 32, 116, 104, 101, 32, 110, 111, 110, 45, 116, 111, 121, 32, 118, 101, 114, 115, 105, 111, 110, 32, 116, 111, 32, 115, 111, 108, 118, 101, 32, 116, 104, 105, 115, 32, 99, 97, 115, 101, 33, 10};
                    print_line(string_mxuecn);
                    return;
                }
                A = A * a0; /* toy version big int operation */
                x = x + 1;
            }else{
                if ((TMP == 0) /* toy version big int comparison */ ) {
                    write_solution_v1(x);
                    if(!assertion) return;
                    write_solution_v1(y);
                    if(!assertion) return;
                    solution_v1[array_pointer] = solution_v1[array_pointer] + 1;
                    if (C > int_threshold / c0) {
                        // "-- [Solver V1] Runtime Warning: exceeding range of int32; try the non-toy version to solve this case!"
                        int string_qivtrf[102] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 82, 117, 110, 116, 105, 109, 101, 32, 87, 97, 114, 110, 105, 110, 103, 58, 32, 101, 120, 99, 101, 101, 100, 105, 110, 103, 32, 114, 97, 110, 103, 101, 32, 111, 102, 32, 105, 110, 116, 51, 50, 59, 32, 116, 114, 121, 32, 116, 104, 101, 32, 110, 111, 110, 45, 116, 111, 121, 32, 118, 101, 114, 115, 105, 111, 110, 32, 116, 111, 32, 115, 111, 108, 118, 101, 32, 116, 104, 105, 115, 32, 99, 97, 115, 101, 33, 10};
                        print_line(string_qivtrf);
                        return;
                    }
                    C = C * c0; /* toy version big int operation */
                    y = y + 1;
                }else{
                    if (C > int_threshold / c0) {
                        // "-- [Solver V1] Runtime Warning: exceeding range of int32; try the non-toy version to solve this case!"
                        int string_fagmwb[102] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 82, 117, 110, 116, 105, 109, 101, 32, 87, 97, 114, 110, 105, 110, 103, 58, 32, 101, 120, 99, 101, 101, 100, 105, 110, 103, 32, 114, 97, 110, 103, 101, 32, 111, 102, 32, 105, 110, 116, 51, 50, 59, 32, 116, 114, 121, 32, 116, 104, 101, 32, 110, 111, 110, 45, 116, 111, 121, 32, 118, 101, 114, 115, 105, 111, 110, 32, 116, 111, 32, 115, 111, 108, 118, 101, 32, 116, 104, 105, 115, 32, 99, 97, 115, 101, 33, 10};
                        print_line(string_fagmwb);
                        return;
                    }
                    C = C * c0; /* toy version big int operation */
                    y = y + 1;
                }
            }
        }
        /* toy version big int resource release of A (do nothing) */
        /* toy version big int resource release of B (do nothing) */
        /* toy version big int resource release of C (do nothing) */
        /* toy version big int resource release of TMP (do nothing) */
        solution_v1[0] = solution_v1_length;
        solver_v1_success = 1;
    }else{
        // -1表示不用枚举，“x < 1或y < 1”一出来，方程肯定就无解了
        write_solution_v1(-1);
        solution_v1[0] = solution_v1_length;
        solver_v1_success = 1;
    }
}


void Solve_Diophantine1_II() {
    if (verbose_v1) {
        // "-- Verbose mode on."
        int string_kqfsmg[20] = {45, 45, 32, 86, 101, 114, 98, 111, 115, 101, 32, 109, 111, 100, 101, 32, 111, 110, 46, 10};
        print_line(string_kqfsmg);
    }
    int A; /* toy version big int declaration */
    int B; /* toy version big int declaration */
    int C; /* toy version big int declaration */
    int TMP; /* toy version big int declaration */
    int THRESHOLD; /* toy version big int declaration */
    A = a_v1; /* toy version big int assignment */
    B = b_v1; /* toy version big int assignment */
    C = c_v1; /* toy version big int assignment */
    THRESHOLD = 1000000000;
    int a0 = a_v1, c0 = c_v1, x0 = 0, x = 1, y0 = 0, y = 1;
    while (1) {
        TMP = A + B; /* toy version big int operation */
        TMP = C - TMP; /* toy version big int operation */
        if ((TMP > 0 /* toy version big int comparison */ )) {
            TMP = THRESHOLD - B; /* toy version big int operation */
            TMP = TMP / a0; /* toy version big int operation */
            if ((A > TMP /* toy version big int comparison */ )) break;
            A = A * a0; /* toy version big int operation */
            x = x + 1;
        }else{
            if ((TMP == 0) /* toy version big int comparison */ ) {
                x0 = x;
                y0 = y;
                TMP = THRESHOLD / c0; /* toy version big int operation */
                if ((C > TMP /* toy version big int comparison */ )) break;
                C = C * c0; /* toy version big int operation */
                y = y + 1;
            }else{
                TMP = THRESHOLD / c0; /* toy version big int operation */
                if ((C > TMP /* toy version big int comparison */ )) break;
                C = C * c0; /* toy version big int operation */
                y = y + 1;
            }
        }
    }
    /* toy version big int resource release of A (do nothing) */
    /* toy version big int resource release of B (do nothing) */
    /* toy version big int resource release of C (do nothing) */
    /* toy version big int resource release of TMP (do nothing) */
    /* toy version big int resource release of THRESHOLD (do nothing) */
    // 从“反设x >= x0” / “反设y >= y0”开始归谬
    x0 = x0 + 1;
    y0 = y0 + 1;
    int prime_list_index = 0;
    // 希望对所有小于500的a, b, c顺利求解，这里开得稍大一点
    while (prime_list[prime_list_index] < 600) {
        if (c_v1 % prime_list[prime_list_index] == 0) {
            // "-- [Solver V1] unknown error encountered in situation II!"
            int array_ratucl[58] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 117, 110, 107, 110, 111, 119, 110, 32, 101, 114, 114, 111, 114, 32, 101, 110, 99, 111, 117, 110, 116, 101, 114, 101, 100, 32, 105, 110, 32, 115, 105, 116, 117, 97, 116, 105, 111, 110, 32, 73, 73, 33, 10};
            assert(a_v1 % prime_list[prime_list_index] != 0, array_ratucl);
            if (!assertion) return;
            insert_disproof_evidence(prime_list[prime_list_index], y0, 2);
        }
        if (a_v1 % prime_list[prime_list_index] == 0) {
            // "-- [Solver V1] unknown error encountered in situation II!"
            int array_eynbgw[58] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 117, 110, 107, 110, 111, 119, 110, 32, 101, 114, 114, 111, 114, 32, 101, 110, 99, 111, 117, 110, 116, 101, 114, 101, 100, 32, 105, 110, 32, 115, 105, 116, 117, 97, 116, 105, 111, 110, 32, 73, 73, 33, 10};
            assert(c_v1 % prime_list[prime_list_index] != 0, array_eynbgw);
            if (!assertion) return;
            insert_disproof_evidence(prime_list[prime_list_index], x0, 1);
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
        if (verbose_v1) {
            if (disproof_type == 1) {
                // "-- Trying to disprove x >= %d with prime factor %d of %d ..."
                int string_lurzpy[61] = {45, 45, 32, 84, 114, 121, 105, 110, 103, 32, 116, 111, 32, 100, 105, 115, 112, 114, 111, 118, 101, 32, 120, 32, 62, 61, 32, 37, 100, 32, 119, 105, 116, 104, 32, 112, 114, 105, 109, 101, 32, 102, 97, 99, 116, 111, 114, 32, 37, 100, 32, 111, 102, 32, 37, 100, 32, 46, 46, 46, 10};
                print_line_with_ddd(string_lurzpy, disproof_power, disproof_prime, a0);
            }else if (disproof_type == 2) {
                // "-- Trying to disprove y >= %d with prime factor %d of %d ..."
                int string_xpsnvo[61] = {45, 45, 32, 84, 114, 121, 105, 110, 103, 32, 116, 111, 32, 100, 105, 115, 112, 114, 111, 118, 101, 32, 121, 32, 62, 61, 32, 37, 100, 32, 119, 105, 116, 104, 32, 112, 114, 105, 109, 101, 32, 102, 97, 99, 116, 111, 114, 32, 37, 100, 32, 111, 102, 32, 37, 100, 32, 46, 46, 46, 10};
                print_line_with_ddd(string_xpsnvo, disproof_power, disproof_prime, c0);
            }else{
                // "-- [Solver V1] unknown error encountered in situation II!"
            int array_xtmggq[58] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 117, 110, 107, 110, 111, 119, 110, 32, 101, 114, 114, 111, 114, 32, 101, 110, 99, 111, 117, 110, 116, 101, 114, 101, 100, 32, 105, 110, 32, 115, 105, 116, 117, 97, 116, 105, 111, 110, 32, 73, 73, 33, 10};
            assert(0, array_xtmggq);
            if (!assertion) return; 
            }
        }
        if (disproof_type == 1) {
            Solve_Diophantine1_II_disproof_A();
            if(!assertion) return;
            if (solver_v1_success) {
                if (verbose_v1) {
                    // "-- Succeeded."
                    int string_tnqhch[14] = {45, 45, 32, 83, 117, 99, 99, 101, 101, 100, 101, 100, 46, 10};
                    print_line(string_tnqhch);
                }
                if (disproof_power > 1) {
                    solution_v1_pointer_backup = solution_v1_pointer;
                    write_solution_v1(0);
                    if(!assertion) return;
                    // 归谬完成，枚举x的有限个取值
                    int A; /* toy version big int declaration */
                    int B; /* toy version big int declaration */
                    int C; /* toy version big int declaration */
                    int TMP; /* toy version big int declaration */
                    A = a_v1; /* toy version big int assignment */
                    B = b_v1; /* toy version big int assignment */
                    C = c_v1; /* toy version big int assignment */
                    int x = 1, y = 1;
                    int a0 = a_v1, c0 = c_v1;
                    while (x < disproof_power) {
                        TMP = A + B; /* toy version big int operation */
                        TMP = C - TMP; /* toy version big int operation */
                        if ((TMP > 0 /* toy version big int comparison */ )) {
                            if (A > int_threshold / a0) {
                                // "-- [Solver V1] Runtime Warning: exceeding range of int32; try the non-toy version to solve this case!"
                                int string_hiodgs[102] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 82, 117, 110, 116, 105, 109, 101, 32, 87, 97, 114, 110, 105, 110, 103, 58, 32, 101, 120, 99, 101, 101, 100, 105, 110, 103, 32, 114, 97, 110, 103, 101, 32, 111, 102, 32, 105, 110, 116, 51, 50, 59, 32, 116, 114, 121, 32, 116, 104, 101, 32, 110, 111, 110, 45, 116, 111, 121, 32, 118, 101, 114, 115, 105, 111, 110, 32, 116, 111, 32, 115, 111, 108, 118, 101, 32, 116, 104, 105, 115, 32, 99, 97, 115, 101, 33, 10};
                                print_line(string_hiodgs);
                                solver_v1_success = 0;
                                return;
                            }
                            A = A * a0; /* toy version big int operation */
                            x = x + 1;
                        }else{
                            if ((TMP == 0) /* toy version big int comparison */ ) {
                                write_solution_v1(x);
                                if(!assertion) return;
                                write_solution_v1(y);
                                if(!assertion) return;
                                solution_v1[solution_v1_pointer_backup] = solution_v1[solution_v1_pointer_backup]+1;
                                if (C > int_threshold / c0) {
                                    // "-- [Solver V1] Runtime Warning: exceeding range of int32; try the non-toy version to solve this case!"
                                    int string_sbkokf[102] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 82, 117, 110, 116, 105, 109, 101, 32, 87, 97, 114, 110, 105, 110, 103, 58, 32, 101, 120, 99, 101, 101, 100, 105, 110, 103, 32, 114, 97, 110, 103, 101, 32, 111, 102, 32, 105, 110, 116, 51, 50, 59, 32, 116, 114, 121, 32, 116, 104, 101, 32, 110, 111, 110, 45, 116, 111, 121, 32, 118, 101, 114, 115, 105, 111, 110, 32, 116, 111, 32, 115, 111, 108, 118, 101, 32, 116, 104, 105, 115, 32, 99, 97, 115, 101, 33, 10};
                                    print_line(string_sbkokf);
                                    solver_v1_success = 0;
                                    return;
                                }
                                C = C * c0; /* toy version big int operation */
                                y = y + 1;
                            }else{
                                if (C > int_threshold / c0) {
                                    // "-- [Solver V1] Runtime Warning: exceeding range of int32; try the non-toy version to solve this case!"
                                    int string_kxpswt[102] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 82, 117, 110, 116, 105, 109, 101, 32, 87, 97, 114, 110, 105, 110, 103, 58, 32, 101, 120, 99, 101, 101, 100, 105, 110, 103, 32, 114, 97, 110, 103, 101, 32, 111, 102, 32, 105, 110, 116, 51, 50, 59, 32, 116, 114, 121, 32, 116, 104, 101, 32, 110, 111, 110, 45, 116, 111, 121, 32, 118, 101, 114, 115, 105, 111, 110, 32, 116, 111, 32, 115, 111, 108, 118, 101, 32, 116, 104, 105, 115, 32, 99, 97, 115, 101, 33, 10};
                                    print_line(string_kxpswt);
                                    solver_v1_success = 0;
                                    return;
                                }
                                C = C * c0; /* toy version big int operation */
                                y = y + 1;
                            }
                        }
                    }
                    /* toy version big int resource release of A (do nothing) */
                    /* toy version big int resource release of B (do nothing) */
                    /* toy version big int resource release of C (do nothing) */
                    /* toy version big int resource release of TMP (do nothing) */
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
                if (verbose_v1) {
                    // "-- Succeeded."
                    int string_jajtwy[14] = {45, 45, 32, 83, 117, 99, 99, 101, 101, 100, 101, 100, 46, 10};
                    print_line(string_jajtwy);
                }
                if (disproof_power > 1) {
                    solution_v1_pointer_backup = solution_v1_pointer;
                    write_solution_v1(0);
                    if(!assertion) return;
                    // 归谬完成，枚举y的有限个取值
                    int A; /* toy version big int declaration */
                    int B; /* toy version big int declaration */
                    int C; /* toy version big int declaration */
                    int TMP; /* toy version big int declaration */
                    A = a_v1; /* toy version big int assignment */
                    B = b_v1; /* toy version big int assignment */
                    C = c_v1; /* toy version big int assignment */
                    int x = 1, y = 1;
                    int a0 = a_v1, c0 = c_v1;
                    while (y < disproof_power) {
                        TMP = A + B; /* toy version big int operation */
                        TMP = C - TMP; /* toy version big int operation */
                        if ((TMP > 0 /* toy version big int comparison */ )) {
                            if (A > int_threshold / a0) {
                                // "-- [Solver V1] Runtime Warning: exceeding range of int32; try the non-toy version to solve this case!"
                                int string_ktopff[102] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 82, 117, 110, 116, 105, 109, 101, 32, 87, 97, 114, 110, 105, 110, 103, 58, 32, 101, 120, 99, 101, 101, 100, 105, 110, 103, 32, 114, 97, 110, 103, 101, 32, 111, 102, 32, 105, 110, 116, 51, 50, 59, 32, 116, 114, 121, 32, 116, 104, 101, 32, 110, 111, 110, 45, 116, 111, 121, 32, 118, 101, 114, 115, 105, 111, 110, 32, 116, 111, 32, 115, 111, 108, 118, 101, 32, 116, 104, 105, 115, 32, 99, 97, 115, 101, 33, 10};
                                print_line(string_ktopff);
                                solver_v1_success = 0;
                                return;
                            }
                            A = A * a0; /* toy version big int operation */
                            x = x + 1;
                        }else{
                            if ((TMP == 0) /* toy version big int comparison */ ) {
                                write_solution_v1(x);
                                if(!assertion) return;
                                write_solution_v1(y);
                                if(!assertion) return;
                                solution_v1[solution_v1_pointer_backup] = solution_v1[solution_v1_pointer_backup]+1;
                                if (C > int_threshold / c0) {
                                    // "-- [Solver V1] Runtime Warning: exceeding range of int32; try the non-toy version to solve this case!"
                                    int string_lairke[102] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 82, 117, 110, 116, 105, 109, 101, 32, 87, 97, 114, 110, 105, 110, 103, 58, 32, 101, 120, 99, 101, 101, 100, 105, 110, 103, 32, 114, 97, 110, 103, 101, 32, 111, 102, 32, 105, 110, 116, 51, 50, 59, 32, 116, 114, 121, 32, 116, 104, 101, 32, 110, 111, 110, 45, 116, 111, 121, 32, 118, 101, 114, 115, 105, 111, 110, 32, 116, 111, 32, 115, 111, 108, 118, 101, 32, 116, 104, 105, 115, 32, 99, 97, 115, 101, 33, 10};
                                    print_line(string_lairke);
                                    solver_v1_success = 0;
                                    return;
                                }
                                C = C * c0; /* toy version big int operation */
                                y = y + 1;
                            }else{
                                if (C > int_threshold / c0) {
                                    // "-- [Solver V1] Runtime Warning: exceeding range of int32; try the non-toy version to solve this case!"
                                    int string_mdqako[102] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 82, 117, 110, 116, 105, 109, 101, 32, 87, 97, 114, 110, 105, 110, 103, 58, 32, 101, 120, 99, 101, 101, 100, 105, 110, 103, 32, 114, 97, 110, 103, 101, 32, 111, 102, 32, 105, 110, 116, 51, 50, 59, 32, 116, 114, 121, 32, 116, 104, 101, 32, 110, 111, 110, 45, 116, 111, 121, 32, 118, 101, 114, 115, 105, 111, 110, 32, 116, 111, 32, 115, 111, 108, 118, 101, 32, 116, 104, 105, 115, 32, 99, 97, 115, 101, 33, 10};
                                    print_line(string_mdqako);
                                    solver_v1_success = 0;
                                    return;
                                }
                                C = C * c0; /* toy version big int operation */
                                y = y + 1;
                            }
                        }
                    }
                    /* toy version big int resource release of A (do nothing) */
                    /* toy version big int resource release of B (do nothing) */
                    /* toy version big int resource release of C (do nothing) */
                    /* toy version big int resource release of TMP (do nothing) */
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
            // "-- [Solver V1] unknown error encountered in situation II!"
            int array_aqdmbj[58] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 117, 110, 107, 110, 111, 119, 110, 32, 101, 114, 114, 111, 114, 32, 101, 110, 99, 111, 117, 110, 116, 101, 114, 101, 100, 32, 105, 110, 32, 115, 105, 116, 117, 97, 116, 105, 111, 110, 32, 73, 73, 33, 10};
            assert(0, array_aqdmbj);
            if (!assertion) return;
        }
        if (power(disproof_prime, disproof_power, -1) < mod_threshold_v1 / disproof_prime) {
            insert_disproof_evidence(disproof_prime, disproof_power+1, disproof_type);
            if(!assertion) return;
        }
    }
    solver_v1_success = 0;
}


void Solve_Diophantine1() {
    // "-- [Solver V1] a, b, c not set, can't solve now!"
    int array_fitjtv[49] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 97, 44, 32, 98, 44, 32, 99, 32, 110, 111, 116, 32, 115, 101, 116, 44, 32, 99, 97, 110, 39, 116, 32, 115, 111, 108, 118, 101, 32, 110, 111, 119, 33, 10};
    assert(abc_set_status_v1, array_fitjtv);
    if (!assertion) return;

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
        while (greatest_common_divisor(a_v1, temp) != 1) temp = temp / greatest_common_divisor(a_v1, temp);
        if(!assertion) return;
        write_solution_v1(temp);
        if(!assertion) return;
        Solve_Diophantine1_I_i();
        return;
    }

    // 情况I - ii
    temp = greatest_common_divisor(a_v1, b_v1);
    if(!assertion) return;
    temp = contain_undividable_prime_part(temp, c_v1);
    if(!assertion) return;
    if (temp) {
        write_solution_v1(1);
        if(!assertion) return;
        write_solution_v1(2);
        if(!assertion) return;
        temp = greatest_common_divisor(a_v1, b_v1);
        while (greatest_common_divisor(c_v1, temp) != 1) temp = temp / greatest_common_divisor(c_v1, temp);
        if(!assertion) return;
        write_solution_v1(temp);
        if(!assertion) return;
        Solve_Diophantine1_I_ii();
        return;
    }

    // 情况I - iii
    temp = greatest_common_divisor(a_v1, c_v1);
    if(!assertion) return;
    if (temp > 1) {
        write_solution_v1(1);
        if(!assertion) return;
        write_solution_v1(3);
        if(!assertion) return;
        write_solution_v1(temp);
        if(!assertion) return;
        Solve_Diophantine1_I_iii();
        return;
    }

    // 情况II
    write_solution_v1(2);
    if(!assertion) return;
    tune_settings(a_v1, b_v1, c_v1);
    Solve_Diophantine1_II();
    if(!assertion) return;
    recover_settings();
    return;
}


void exhaust_solution_v1(int nsolutions_pointer) {
    int a = solution_v1[1];
    int b = solution_v1[2];
    int c = solution_v1[3];
    int nsolutions = solution_v1[nsolutions_pointer];
    if (nsolutions == -1) {
        // "So %d ^ %s + %d = %d ^ %s is impossible."
        int string_gcaozj[41] = {83, 111, 32, 37, 100, 32, 94, 32, 37, 115, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 37, 115, 32, 105, 115, 32, 105, 109, 112, 111, 115, 115, 105, 98, 108, 101, 46, 10};
        print_line_with_dsdds(string_gcaozj, a, x_name_v1, b, c, y_name_v1);
    }else if (nsolutions == 0) {
        // "Further examination shows that %d ^ %s + %d = %d ^ %s is impossible."
        int string_quqtyf[69] = {70, 117, 114, 116, 104, 101, 114, 32, 101, 120, 97, 109, 105, 110, 97, 116, 105, 111, 110, 32, 115, 104, 111, 119, 115, 32, 116, 104, 97, 116, 32, 37, 100, 32, 94, 32, 37, 115, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 37, 115, 32, 105, 115, 32, 105, 109, 112, 111, 115, 115, 105, 98, 108, 101, 46, 10};
        print_line_with_dsdds(string_quqtyf, a, x_name_v1, b, c, y_name_v1);
    }else{
        // "Further examination shows that "
        int string_addrof[32] = {70, 117, 114, 116, 104, 101, 114, 32, 101, 120, 97, 109, 105, 110, 97, 116, 105, 111, 110, 32, 115, 104, 111, 119, 115, 32, 116, 104, 97, 116, 32, 0};
        print_word(string_addrof);
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
    // "-- [Solver V1] solver failed or name not set, can't print solution!"
    int array_steptc[68] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 115, 111, 108, 118, 101, 114, 32, 102, 97, 105, 108, 101, 100, 32, 111, 114, 32, 110, 97, 109, 101, 32, 110, 111, 116, 32, 115, 101, 116, 44, 32, 99, 97, 110, 39, 116, 32, 112, 114, 105, 110, 116, 32, 115, 111, 108, 117, 116, 105, 111, 110, 33, 10};
    assert(solver_v1_success && xy_name_set_status_v1, array_steptc);
    if (!assertion) return;
    int a = solution_v1[1];
    int b = solution_v1[2];
    int c = solution_v1[3];
    // "For positive integers %s, %s satisfying %d ^ %s + %d = %d ^ %s,"
    int string_vzcair[64] = {70, 111, 114, 32, 112, 111, 115, 105, 116, 105, 118, 101, 32, 105, 110, 116, 101, 103, 101, 114, 115, 32, 37, 115, 44, 32, 37, 115, 32, 115, 97, 116, 105, 115, 102, 121, 105, 110, 103, 32, 37, 100, 32, 94, 32, 37, 115, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 37, 115, 44, 10};
    print_line_with_ssdsdds(string_vzcair, x_name_v1, y_name_v1, a, x_name_v1, b, c, y_name_v1);
    int i;
    if (solution_v1[4] == 1) {
        if (solution_v1[5] == 1) {
            // "this is impossible, because it implies that %d ^ %s = 0 (mod %d)."
            int string_yksbrq[66] = {116, 104, 105, 115, 32, 105, 115, 32, 105, 109, 112, 111, 115, 115, 105, 98, 108, 101, 44, 32, 98, 101, 99, 97, 117, 115, 101, 32, 105, 116, 32, 105, 109, 112, 108, 105, 101, 115, 32, 116, 104, 97, 116, 32, 37, 100, 32, 94, 32, 37, 115, 32, 61, 32, 48, 32, 40, 109, 111, 100, 32, 37, 100, 41, 46, 10};
            print_line_with_dsd(string_yksbrq, a, x_name_v1, solution_v1[6]);
        }else if (solution_v1[5] == 2) {
            // "this is impossible, because it implies that %d ^ %s = 0 (mod %d)."
            int string_cuwpdz[66] = {116, 104, 105, 115, 32, 105, 115, 32, 105, 109, 112, 111, 115, 115, 105, 98, 108, 101, 44, 32, 98, 101, 99, 97, 117, 115, 101, 32, 105, 116, 32, 105, 109, 112, 108, 105, 101, 115, 32, 116, 104, 97, 116, 32, 37, 100, 32, 94, 32, 37, 115, 32, 61, 32, 48, 32, 40, 109, 111, 100, 32, 37, 100, 41, 46, 10};
            print_line_with_dsd(string_cuwpdz, c, y_name_v1, solution_v1[6]);
        }else if (solution_v1[5] == 3) {
            // "if %s >= %d and %s >= %d,"
            int string_ujljni[26] = {105, 102, 32, 37, 115, 32, 62, 61, 32, 37, 100, 32, 97, 110, 100, 32, 37, 115, 32, 62, 61, 32, 37, 100, 44, 10};
            print_line_with_sdsd(string_ujljni, x_name_v1, solution_v1[7], y_name_v1, solution_v1[7]);
            // "%d = 0 (mod %d), which is impossible."
            int string_wvcyqv[38] = {37, 100, 32, 61, 32, 48, 32, 40, 109, 111, 100, 32, 37, 100, 41, 44, 32, 119, 104, 105, 99, 104, 32, 105, 115, 32, 105, 109, 112, 111, 115, 115, 105, 98, 108, 101, 46, 10};
            print_line_with_dd(string_wvcyqv, b, power(solution_v1[6], solution_v1[7], -1));
            // "Therefore, %s < %d or %s < %d."
            int string_sltzhv[31] = {84, 104, 101, 114, 101, 102, 111, 114, 101, 44, 32, 37, 115, 32, 60, 32, 37, 100, 32, 111, 114, 32, 37, 115, 32, 60, 32, 37, 100, 46, 10};
            print_line_with_sdsd(string_sltzhv, x_name_v1, solution_v1[7], y_name_v1, solution_v1[7]);
            int nsolutions_pointer = 8;
            exhaust_solution_v1(nsolutions_pointer);
        }else {
            // "-- [Solver V1] solution vector format is incorrect for unknown reason!"
            int array_nmltgw[71] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 115, 111, 108, 117, 116, 105, 111, 110, 32, 118, 101, 99, 116, 111, 114, 32, 102, 111, 114, 109, 97, 116, 32, 105, 115, 32, 105, 110, 99, 111, 114, 114, 101, 99, 116, 32, 102, 111, 114, 32, 117, 110, 107, 110, 111, 119, 110, 32, 114, 101, 97, 115, 111, 110, 33, 10};
            assert(0, array_nmltgw);
            if (!assertion) return;
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
            // "if %s >= %d, %d ^ %s = %d (mod %d)."
            int string_vcwgmp[36] = {105, 102, 32, 37, 115, 32, 62, 61, 32, 37, 100, 44, 32, 37, 100, 32, 94, 32, 37, 115, 32, 61, 32, 37, 100, 32, 40, 109, 111, 100, 32, 37, 100, 41, 46, 10};
            print_line_with_sddsdd(string_vcwgmp, x_name_v1, dp_power, c, y_name_v1, R, M);
            int yr = read_solution_v1();
            if (yr == -1) {
                // "However, this is impossible."
                int string_jawefu[29] = {72, 111, 119, 101, 118, 101, 114, 44, 32, 116, 104, 105, 115, 32, 105, 115, 32, 105, 109, 112, 111, 115, 115, 105, 98, 108, 101, 46, 10};
                print_line(string_jawefu);
                // "Therefore, %s < %d."
                int string_iwshay[20] = {84, 104, 101, 114, 101, 102, 111, 114, 101, 44, 32, 37, 115, 32, 60, 32, 37, 100, 46, 10};
                print_line_with_sd(string_iwshay, x_name_v1, dp_power);
                exhaust_solution_v1(solution_v1_pointer);
            }else{
                int k = read_solution_v1();
                int P = read_solution_v1();
                int m = read_solution_v1();
                int npossibilities = read_solution_v1();
                // k m 不等，x = xr (mod k) 推出多个关于m的可能余数
                if (k != m) {
                    // "So %s = %d (mod %d), "
                    int string_csmtrq[22] = {83, 111, 32, 37, 115, 32, 61, 32, 37, 100, 32, 40, 109, 111, 100, 32, 37, 100, 41, 44, 32, 10};
                    print_line_with_sdd(string_csmtrq, y_name_v1, yr, k);
                    // "which implies "
                    int string_mucfrh[15] = {119, 104, 105, 99, 104, 32, 105, 109, 112, 108, 105, 101, 115, 32, 0};
                    print_word(string_mucfrh);
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
                    // " (mod %d)."
                    int string_pmnlti[11] = {32, 40, 109, 111, 100, 32, 37, 100, 41, 46, 10};
                    print_line_with_d(string_pmnlti, m);
                // k m 相等，npossibilities = 1
                }else {
                    // "So %s = %d (mod %d), "
                    int string_shgdfd[22] = {83, 111, 32, 37, 115, 32, 61, 32, 37, 100, 32, 40, 109, 111, 100, 32, 37, 100, 41, 44, 32, 10};
                    print_line_with_sdd(string_shgdfd, y_name_v1, yr, k);
                    read_solution_v1();
                }
                read_solution_v1();
                // "Therefore, "
                int string_ntefms[12] = {84, 104, 101, 114, 101, 102, 111, 114, 101, 44, 32, 0};
                print_word(string_ntefms);
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
                // " (mod %d)."
                int string_znhcff[11] = {32, 40, 109, 111, 100, 32, 37, 100, 41, 46, 10};
                print_line_with_d(string_znhcff, P);
                read_solution_v1();
                read_solution_v1();
                // "So "
                int string_eanhzo[4] = {83, 111, 32, 0};
                print_word(string_eanhzo);
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
                // " (mod %d), but this is impossible."
                int string_sdwmwo[35] = {32, 40, 109, 111, 100, 32, 37, 100, 41, 44, 32, 98, 117, 116, 32, 116, 104, 105, 115, 32, 105, 115, 32, 105, 109, 112, 111, 115, 115, 105, 98, 108, 101, 46, 10};
                print_line_with_d(string_sdwmwo, P);
                // "Therefore, %s < %d."
                int string_mlebym[20] = {84, 104, 101, 114, 101, 102, 111, 114, 101, 44, 32, 37, 115, 32, 60, 32, 37, 100, 46, 10};
                print_line_with_sd(string_mlebym, x_name_v1, dp_power);
                read_solution_v1();
                exhaust_solution_v1(solution_v1_pointer);
            }
        // Front Mode: Obtain x = xr (mod k) by disproof assumption and search series {n*k + 1} for an appropriate prime number
        }else if (dp_type == 2){
            read_solution_v1();
            int R = read_solution_v1();
            int M = read_solution_v1();
            // "if %s >= %d, %d ^ %s = %d (mod %d)."
            int string_vkbqbd[36] = {105, 102, 32, 37, 115, 32, 62, 61, 32, 37, 100, 44, 32, 37, 100, 32, 94, 32, 37, 115, 32, 61, 32, 37, 100, 32, 40, 109, 111, 100, 32, 37, 100, 41, 46, 10};
            print_line_with_sddsdd(string_vkbqbd, y_name_v1, dp_power, a, x_name_v1, R, M);
            int xr = read_solution_v1();
            if (xr == -1) {
                // "However, this is impossible."
                int string_ohzdtp[29] = {72, 111, 119, 101, 118, 101, 114, 44, 32, 116, 104, 105, 115, 32, 105, 115, 32, 105, 109, 112, 111, 115, 115, 105, 98, 108, 101, 46, 10};
                print_line(string_ohzdtp);
                // "Therefore, %s < %d."
                int string_ufnllw[20] = {84, 104, 101, 114, 101, 102, 111, 114, 101, 44, 32, 37, 115, 32, 60, 32, 37, 100, 46, 10};
                print_line_with_sd(string_ufnllw, y_name_v1, dp_power);
                exhaust_solution_v1(solution_v1_pointer);
            }else{
                int k = read_solution_v1();
                int P = read_solution_v1();
                int m = read_solution_v1();
                int npossibilities = read_solution_v1();
                // k m 不等，x = xr (mod k) 推出多个关于m的可能余数
                if (k != m) {
                    // "So %s = %d (mod %d), "
                    int string_zhqpty[22] = {83, 111, 32, 37, 115, 32, 61, 32, 37, 100, 32, 40, 109, 111, 100, 32, 37, 100, 41, 44, 32, 10};
                    print_line_with_sdd(string_zhqpty, x_name_v1, xr, k);
                    // "which implies "
                    int string_ffreeb[15] = {119, 104, 105, 99, 104, 32, 105, 109, 112, 108, 105, 101, 115, 32, 0};
                    print_word(string_ffreeb);
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
                    // " (mod %d)."
                    int string_alphgs[11] = {32, 40, 109, 111, 100, 32, 37, 100, 41, 46, 10};
                    print_line_with_d(string_alphgs, m);
                // k m 相等，npossibilities = 1
                }else {
                    // "So %s = %d (mod %d)."
                    int string_slryuq[21] = {83, 111, 32, 37, 115, 32, 61, 32, 37, 100, 32, 40, 109, 111, 100, 32, 37, 100, 41, 46, 10};
                    print_line_with_sdd(string_slryuq, x_name_v1, xr, k);
                    read_solution_v1();
                }
                read_solution_v1();
                // "Therefore, "
                int string_ryloqx[12] = {84, 104, 101, 114, 101, 102, 111, 114, 101, 44, 32, 0};
                print_word(string_ryloqx);
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
                // " (mod %d)."
                int string_vbehto[11] = {32, 40, 109, 111, 100, 32, 37, 100, 41, 46, 10};
                print_line_with_d(string_vbehto, P);
                read_solution_v1();
                read_solution_v1();
                // "So "
                int string_hdrsyn[4] = {83, 111, 32, 0};
                print_word(string_hdrsyn);
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
                // " (mod %d), but this is impossible."
                int string_mcblig[35] = {32, 40, 109, 111, 100, 32, 37, 100, 41, 44, 32, 98, 117, 116, 32, 116, 104, 105, 115, 32, 105, 115, 32, 105, 109, 112, 111, 115, 115, 105, 98, 108, 101, 46, 10};
                print_line_with_d(string_mcblig, P);
                // "Therefore, %s < %d."
                int string_czvoyz[20] = {84, 104, 101, 114, 101, 102, 111, 114, 101, 44, 32, 37, 115, 32, 60, 32, 37, 100, 46, 10};
                print_line_with_sd(string_czvoyz, y_name_v1, dp_power);
                read_solution_v1();
                exhaust_solution_v1(solution_v1_pointer);
            }
        }else{
        // "-- [Solver V1] solution vector format is incorrect for unknown reason!"
            int array_rhbtmq[71] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 115, 111, 108, 117, 116, 105, 111, 110, 32, 118, 101, 99, 116, 111, 114, 32, 102, 111, 114, 109, 97, 116, 32, 105, 115, 32, 105, 110, 99, 111, 114, 114, 101, 99, 116, 32, 102, 111, 114, 32, 117, 110, 107, 110, 111, 119, 110, 32, 114, 101, 97, 115, 111, 110, 33, 10};
            assert(0, array_rhbtmq);
            if (!assertion) return;
        }
    }else{
        // "-- [Solver V1] solution vector format is incorrect for unknown reason!"
        int array_xepqmc[71] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 115, 111, 108, 117, 116, 105, 111, 110, 32, 118, 101, 99, 116, 111, 114, 32, 102, 111, 114, 109, 97, 116, 32, 105, 115, 32, 105, 110, 99, 111, 114, 114, 101, 99, 116, 32, 102, 111, 114, 32, 117, 110, 107, 110, 111, 119, 110, 32, 114, 101, 97, 115, 111, 110, 33, 10};
        assert(0, array_xepqmc);
        if (!assertion) return;
    }
}


void print_Lean4_prop_v1 (int nsolutions_pointer, int bracket_multiple) {
    int nsolutions = solution_v1[nsolutions_pointer];
    // 有 -1 和 0 两种情况（-1用于向 print_solution_v1 函数传递信息，解的个数也为 0）
    if (nsolutions <= 0) {
        // "False"
        int string_jirwis[6] = {70, 97, 108, 115, 101, 0};
        print_word(string_jirwis);
        return;
    }
    if (bracket_multiple) putch(left_parenthesis);
    // "List.Mem (x, y) ["
    int string_hyvoli[18] = {76, 105, 115, 116, 46, 77, 101, 109, 32, 40, 120, 44, 32, 121, 41, 32, 91, 0};
    print_word(string_hyvoli);
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
    // "]"
    int string_izknzr[2] = {93, 0};
    print_word(string_izknzr);
    if (bracket_multiple) putch(right_parenthesis);
}


void print_Lean4_int_array (int nsolutions_pointer) {
    int nint = solution_v1[nsolutions_pointer];
    int offset = 1;
    while (offset <= nint) {
        if (offset >= 2) {
            putch(comma);
            putch(space);
        }
        putint(solution_v1[nsolutions_pointer+offset]);
        offset = offset + 1;
    }
}


 void generate_Lean4_code_v1 () {
    // "-- [Solver V1] solver failed or name not set, can't generate Lean4 code!"
    int array_okejtq[73] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 115, 111, 108, 118, 101, 114, 32, 102, 97, 105, 108, 101, 100, 32, 111, 114, 32, 110, 97, 109, 101, 32, 110, 111, 116, 32, 115, 101, 116, 44, 32, 99, 97, 110, 39, 116, 32, 103, 101, 110, 101, 114, 97, 116, 101, 32, 76, 101, 97, 110, 52, 32, 99, 111, 100, 101, 33, 10};
    assert(solver_v1_success && xy_name_set_status_v1, array_okejtq);
    if (!assertion) return;
    int a = solution_v1[1];
    int b = solution_v1[2];
    int c = solution_v1[3];
    int class = solution_v1[4];
    if (class == 1) {
        int type = solution_v1[5];
        // a ^ x = 0 (mod M) is impossible
        // e.g. 3 ^ x + 6 = 8 ^ y
        if (type == 1) {
            // "/-"
            int string_tfoyls[3] = {47, 45, 10};
            print_line(string_tfoyls);
            // "(Class I, Type i)   %d ^ x + %d = %d ^ y"
            int string_dzpgeo[41] = {40, 67, 108, 97, 115, 115, 32, 73, 44, 32, 84, 121, 112, 101, 32, 105, 41, 32, 32, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 10};
            print_line_with_ddd(string_dzpgeo, a, b, c);
            print_solution_v1();
            // "-/"
            int string_oczxld[3] = {45, 47, 10};
            print_line(string_oczxld);
            int M = solution_v1[6];
            // "theorem diophantine1_%d_%d_%d (x : Nat) (y : Nat) (h1 : x >= 1) (h2 : y >= 1) (h3 : %d ^ x + %d = %d ^ y) :"
            int string_vmsnhv[108] = {116, 104, 101, 111, 114, 101, 109, 32, 100, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 49, 95, 37, 100, 95, 37, 100, 95, 37, 100, 32, 40, 120, 32, 58, 32, 78, 97, 116, 41, 32, 40, 121, 32, 58, 32, 78, 97, 116, 41, 32, 40, 104, 49, 32, 58, 32, 120, 32, 62, 61, 32, 49, 41, 32, 40, 104, 50, 32, 58, 32, 121, 32, 62, 61, 32, 49, 41, 32, 40, 104, 51, 32, 58, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 41, 32, 58, 10};
            print_line_with_dddddd(string_vmsnhv, a, b, c, a, b, c);
            // "  False"
            int string_zgojxn[8] = {32, 32, 70, 97, 108, 115, 101, 10};
            print_line(string_zgojxn);
            // "  := by"
            int string_wwhuky[8] = {32, 32, 58, 61, 32, 98, 121, 10};
            print_line(string_wwhuky);
            // "  have h4 : x % 1 = 0 := by omega"
            int string_nvhhpz[34] = {32, 32, 104, 97, 118, 101, 32, 104, 52, 32, 58, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
            print_line(string_nvhhpz);
            // "  have h5 : y % 1 = 0 := by omega"
            int string_mdoioo[34] = {32, 32, 104, 97, 118, 101, 32, 104, 53, 32, 58, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
            print_line(string_mdoioo);   
            // "  have h6 := Claim (%d ^ y \% %d = 0) ["
            int string_liesog[40] = {32, 32, 104, 97, 118, 101, 32, 104, 54, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 40, 37, 100, 32, 94, 32, 121, 32, 92, 37, 32, 37, 100, 32, 61, 32, 48, 41, 32, 91, 10};
            print_line_with_dd(string_liesog, c, M);   
            // "    {prop := y % 1 = 0, proof := h5},"
            int string_ubtsvk[38] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 53, 125, 44, 10};
            print_line(string_ubtsvk);
            // "    {prop := y >= 1, proof := h2},"
            int string_rvzman[35] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 50, 125, 44, 10};
            print_line(string_rvzman);   
            // "  ] "pow_mod_eq_zero""
            int string_pwwlnl[22] = {32, 32, 93, 32, 34, 112, 111, 119, 95, 109, 111, 100, 95, 101, 113, 95, 122, 101, 114, 111, 34, 10};
            print_line(string_pwwlnl);   
            // "  have h7 : %d ^ x \% %d = 0 := by omega"
            int string_skremz[41] = {32, 32, 104, 97, 118, 101, 32, 104, 55, 32, 58, 32, 37, 100, 32, 94, 32, 120, 32, 92, 37, 32, 37, 100, 32, 61, 32, 48, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
            print_line_with_dd(string_skremz, a, M);   
            // "  have h8 := Claim False ["
            int string_isqwww[27] = {32, 32, 104, 97, 118, 101, 32, 104, 56, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 70, 97, 108, 115, 101, 32, 91, 10};
            print_line(string_isqwww);   
            // "    {prop := x % 1 = 0, proof := h4},"
            int string_jistwa[38] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 52, 125, 44, 10};
            print_line(string_jistwa);
            // "    {prop := x >= 1, proof := h1},"
            int string_bqxztl[35] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 49, 125, 44, 10};
            print_line(string_bqxztl);   
            // "    {prop := %d ^ x \% %d = 0, proof := h7},"
            int string_cqwlsx[45] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 37, 100, 32, 94, 32, 120, 32, 92, 37, 32, 37, 100, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 55, 125, 44, 10};
            print_line_with_dd(string_cqwlsx, a, M);
            // "  ] "observe_mod_cycle""
            int string_buhjdn[24] = {32, 32, 93, 32, 34, 111, 98, 115, 101, 114, 118, 101, 95, 109, 111, 100, 95, 99, 121, 99, 108, 101, 34, 10};
            print_line(string_buhjdn);
            // "  exact h8"
            int string_ouecwq[11] = {32, 32, 101, 120, 97, 99, 116, 32, 104, 56, 10};
            print_line(string_ouecwq);
        // c ^ y = 0 (mod M) is impossible
        // e.g. 3 ^ x + 6 = 11 ^ y
        }else if (type == 2) {
           // "/-"
            int string_gxdlgg[3] = {47, 45, 10};
            print_line(string_gxdlgg);
            // "(Class I, Type ii)   %d ^ x + %d = %d ^ y"
            int string_auxrel[42] = {40, 67, 108, 97, 115, 115, 32, 73, 44, 32, 84, 121, 112, 101, 32, 105, 105, 41, 32, 32, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 10};
            print_line_with_ddd(string_auxrel, a, b, c);
            print_solution_v1();
            // "-/"
            int string_ipqlgv[3] = {45, 47, 10};
            print_line(string_ipqlgv);
            int M = solution_v1[6];
            // "theorem diophantine1_%d_%d_%d (x : Nat) (y : Nat) (h1 : x >= 1) (h2 : y >= 1) (h3 : %d ^ x + %d = %d ^ y) :"
            int string_fkmgoo[108] = {116, 104, 101, 111, 114, 101, 109, 32, 100, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 49, 95, 37, 100, 95, 37, 100, 95, 37, 100, 32, 40, 120, 32, 58, 32, 78, 97, 116, 41, 32, 40, 121, 32, 58, 32, 78, 97, 116, 41, 32, 40, 104, 49, 32, 58, 32, 120, 32, 62, 61, 32, 49, 41, 32, 40, 104, 50, 32, 58, 32, 121, 32, 62, 61, 32, 49, 41, 32, 40, 104, 51, 32, 58, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 41, 32, 58, 10};
            print_line_with_dddddd(string_fkmgoo, a, b, c, a, b, c);
            // "  False"
            int string_zhzrho[8] = {32, 32, 70, 97, 108, 115, 101, 10};
            print_line(string_zhzrho);
            // "  := by"
            int string_rtbpmx[8] = {32, 32, 58, 61, 32, 98, 121, 10};
            print_line(string_rtbpmx);
            // "  have h4 : x % 1 = 0 := by omega"
            int string_hupjqq[34] = {32, 32, 104, 97, 118, 101, 32, 104, 52, 32, 58, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
            print_line(string_hupjqq);
            // "  have h5 : y % 1 = 0 := by omega"
            int string_rsrvqx[34] = {32, 32, 104, 97, 118, 101, 32, 104, 53, 32, 58, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
            print_line(string_rsrvqx);   
            // "  have h6 := Claim (%d ^ x \% %d = 0) ["
            int string_qilptc[40] = {32, 32, 104, 97, 118, 101, 32, 104, 54, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 40, 37, 100, 32, 94, 32, 120, 32, 92, 37, 32, 37, 100, 32, 61, 32, 48, 41, 32, 91, 10};
            print_line_with_dd(string_qilptc, a, M);   
            // "    {prop := x % 1 = 0, proof := h4},"
            int string_htedoz[38] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 52, 125, 44, 10};
            print_line(string_htedoz);
            // "    {prop := x >= 1, proof := h1},"
            int string_nxvgvm[35] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 49, 125, 44, 10};
            print_line(string_nxvgvm);   
            // "  ] "pow_mod_eq_zero""
            int string_uticzd[22] = {32, 32, 93, 32, 34, 112, 111, 119, 95, 109, 111, 100, 95, 101, 113, 95, 122, 101, 114, 111, 34, 10};
            print_line(string_uticzd);   
            // "  have h7 : %d ^ y \% %d = 0 := by omega"
            int string_zwszzu[41] = {32, 32, 104, 97, 118, 101, 32, 104, 55, 32, 58, 32, 37, 100, 32, 94, 32, 121, 32, 92, 37, 32, 37, 100, 32, 61, 32, 48, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
            print_line_with_dd(string_zwszzu, c, M);   
            // "  have h8 := Claim False ["
            int string_juanlr[27] = {32, 32, 104, 97, 118, 101, 32, 104, 56, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 70, 97, 108, 115, 101, 32, 91, 10};
            print_line(string_juanlr);   
            // "    {prop := y % 1 = 0, proof := h5},"
            int string_rpvycg[38] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 53, 125, 44, 10};
            print_line(string_rpvycg);
            // "    {prop := y >= 1, proof := h2},"
            int string_awoxfb[35] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 50, 125, 44, 10};
            print_line(string_awoxfb);   
            // "    {prop := %d ^ y \% %d = 0, proof := h7},"
            int string_vxhkdy[45] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 37, 100, 32, 94, 32, 121, 32, 92, 37, 32, 37, 100, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 55, 125, 44, 10};
            print_line_with_dd(string_vxhkdy, c, M);
            // "  ] "observe_mod_cycle""
            int string_hmcxdl[24] = {32, 32, 93, 32, 34, 111, 98, 115, 101, 114, 118, 101, 95, 109, 111, 100, 95, 99, 121, 99, 108, 101, 34, 10};
            print_line(string_hmcxdl);
            // "  exact h8"
            int string_rtykte[11] = {32, 32, 101, 120, 97, 99, 116, 32, 104, 56, 10};
            print_line(string_rtykte);
        // x >= n and y >= n => b = 0 (mod P ^ n) (×), so x < n or y < n
        // e.g. 2 ^ x + 4 = 6 ^ y
        }else if (type == 3) {
            // "/-"
            int string_kcmkya[3] = {47, 45, 10};
            print_line(string_kcmkya);
            // "(Class I, Type iii)   %d ^ x + %d = %d ^ y"
            int string_jlywcr[43] = {40, 67, 108, 97, 115, 115, 32, 73, 44, 32, 84, 121, 112, 101, 32, 105, 105, 105, 41, 32, 32, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 10};
            print_line_with_ddd(string_jlywcr, a, b, c);
            print_solution_v1();
            // "-/"
            int string_ozjked[3] = {45, 47, 10};
            print_line(string_ozjked);
            // "theorem diophantine1_%d_%d_%d (x : Nat) (y : Nat) (h1 : x >= 1) (h2 : y >= 1) (h3 : %d ^ x + %d = %d ^ y) :"
            int string_wlrqpa[108] = {116, 104, 101, 111, 114, 101, 109, 32, 100, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 49, 95, 37, 100, 95, 37, 100, 95, 37, 100, 32, 40, 120, 32, 58, 32, 78, 97, 116, 41, 32, 40, 121, 32, 58, 32, 78, 97, 116, 41, 32, 40, 104, 49, 32, 58, 32, 120, 32, 62, 61, 32, 49, 41, 32, 40, 104, 50, 32, 58, 32, 121, 32, 62, 61, 32, 49, 41, 32, 40, 104, 51, 32, 58, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 41, 32, 58, 10};
            print_line_with_dddddd(string_wlrqpa, a, b, c, a, b, c);
            // "  "
            int string_ugdobt[3] = {32, 32, 0};
            print_word(string_ugdobt);
            print_Lean4_prop_v1(8, 0);
            print_line(newline);
            // "  := by"
            int string_ffwidx[8] = {32, 32, 58, 61, 32, 98, 121, 10};
            print_line(string_ffwidx);
            // "  have h4 : x % 1 = 0 := by omega"
            int string_awddge[34] = {32, 32, 104, 97, 118, 101, 32, 104, 52, 32, 58, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
            print_line(string_awddge);
            // "  have h5 : y % 1 = 0 := by omega"
            int string_raaugi[34] = {32, 32, 104, 97, 118, 101, 32, 104, 53, 32, 58, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
            print_line(string_raaugi);  
            int gcd = solution_v1[6];
            int dp_power = solution_v1[7];
            // "  by_cases h6 : And (x >= %d) (y >= %d)"
            int string_ebtntm[40] = {32, 32, 98, 121, 95, 99, 97, 115, 101, 115, 32, 104, 54, 32, 58, 32, 65, 110, 100, 32, 40, 120, 32, 62, 61, 32, 37, 100, 41, 32, 40, 121, 32, 62, 61, 32, 37, 100, 41, 10};
            print_line_with_dd(string_ebtntm, dp_power, dp_power);
            // "  have h7 := Claim (%d ^ x \% %d = 0) ["
            int string_uncnyb[40] = {32, 32, 104, 97, 118, 101, 32, 104, 55, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 40, 37, 100, 32, 94, 32, 120, 32, 92, 37, 32, 37, 100, 32, 61, 32, 48, 41, 32, 91, 10};
            print_line_with_dd(string_uncnyb, a, power(gcd, dp_power, -1));   
            // "    {prop := x % 1 = 0, proof := h4},"
            int string_uwnlzb[38] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 52, 125, 44, 10};
            print_line(string_uwnlzb);
            // "    {prop := x >= %d, proof := h6.left},"
            int string_mkrmxb[41] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 62, 61, 32, 37, 100, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 54, 46, 108, 101, 102, 116, 125, 44, 10};
            print_line_with_d(string_mkrmxb, dp_power);   
            // "  ] "pow_mod_eq_zero""
            int string_cpbhqo[22] = {32, 32, 93, 32, 34, 112, 111, 119, 95, 109, 111, 100, 95, 101, 113, 95, 122, 101, 114, 111, 34, 10};
            print_line(string_cpbhqo);   
            // "  have h8 := Claim (%d ^ y \% %d = 0) ["
            int string_iznlpc[40] = {32, 32, 104, 97, 118, 101, 32, 104, 56, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 40, 37, 100, 32, 94, 32, 121, 32, 92, 37, 32, 37, 100, 32, 61, 32, 48, 41, 32, 91, 10};
            print_line_with_dd(string_iznlpc, c, power(gcd, dp_power, -1));   
            // "    {prop := y % 1 = 0, proof := h5},"
            int string_swqtsf[38] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 53, 125, 44, 10};
            print_line(string_swqtsf);
            // "    {prop := y >= %d, proof := h6.right},"
            int string_lfilkc[42] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 62, 61, 32, 37, 100, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 54, 46, 114, 105, 103, 104, 116, 125, 44, 10};
            print_line_with_d(string_lfilkc, dp_power);   
            // "  ] "pow_mod_eq_zero""
            int string_lrjdxb[22] = {32, 32, 93, 32, 34, 112, 111, 119, 95, 109, 111, 100, 95, 101, 113, 95, 122, 101, 114, 111, 34, 10};
            print_line(string_lrjdxb); 
            // "  omega"
            int string_vcctvo[8] = {32, 32, 111, 109, 101, 103, 97, 10};
            print_line(string_vcctvo);
            // "  have h7 : Or (x <= %d) (y <= %d) := by omega"
            int string_poidjr[47] = {32, 32, 104, 97, 118, 101, 32, 104, 55, 32, 58, 32, 79, 114, 32, 40, 120, 32, 60, 61, 32, 37, 100, 41, 32, 40, 121, 32, 60, 61, 32, 37, 100, 41, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
            print_line_with_dd(string_poidjr, dp_power-1, dp_power-1);
            // "  have h8 := Claim "
            int string_twszpj[20] = {32, 32, 104, 97, 118, 101, 32, 104, 56, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 0};
            print_word(string_twszpj);
            print_Lean4_prop_v1(8, 1);
            // " ["
            int string_pfrfcv[3] = {32, 91, 10};
            print_line(string_pfrfcv);
            // "    {prop :=  x % 1 = 0, proof := h4},"
            int string_jtouvz[39] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 52, 125, 44, 10};
            print_line(string_jtouvz);
            // "    {prop :=  x >= 1, proof := h1},"
            int string_vpqayv[36] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 120, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 49, 125, 44, 10};
            print_line(string_vpqayv);
            // "    {prop :=  y % 1 = 0, proof := h5},"
            int string_gesiia[39] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 53, 125, 44, 10};
            print_line(string_gesiia);
            // "    {prop :=  y >= 1, proof := h2},"
            int string_wokdqa[36] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 121, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 50, 125, 44, 10};
            print_line(string_wokdqa);
            // "    {prop := %d ^ x + %d = %d ^ y, proof := h3},"
            int string_tfkijs[49] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 51, 125, 44, 10};
            print_line_with_ddd(string_tfkijs, a, b, c);
            // "    {prop := Or (x <= %d) (y <= %d), proof := h7},"
            int string_uocbeq[51] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 79, 114, 32, 40, 120, 32, 60, 61, 32, 37, 100, 41, 32, 40, 121, 32, 60, 61, 32, 37, 100, 41, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 55, 125, 44, 10};
            print_line_with_dd(string_uocbeq, dp_power-1, dp_power-1);
            // "  ] "diophantine1_enumeration""
            int string_rhrmlh[31] = {32, 32, 93, 32, 34, 100, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 49, 95, 101, 110, 117, 109, 101, 114, 97, 116, 105, 111, 110, 34, 10};
            print_line(string_rhrmlh);
            // "  exact h8"
            int string_tclhrm[11] = {32, 32, 101, 120, 97, 99, 116, 32, 104, 56, 10};
            print_line(string_tclhrm);
        }else{
            // "-- [Solver V1] solution vector format is incorrect for unknown reason!"
            int array_rbkpah[71] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 115, 111, 108, 117, 116, 105, 111, 110, 32, 118, 101, 99, 116, 111, 114, 32, 102, 111, 114, 109, 97, 116, 32, 105, 115, 32, 105, 110, 99, 111, 114, 114, 101, 99, 116, 32, 102, 111, 114, 32, 117, 110, 107, 110, 111, 119, 110, 32, 114, 101, 97, 115, 111, 110, 33, 10};
            assert(0, array_rbkpah);
            if (!assertion) return;
        }    
    }else if (class == 2){
        int dp_prime = solution_v1[5];
        int dp_power = solution_v1[6];
        int dp_type = solution_v1[7];
        solution_v1_pointer = 8;
        // Back Mode: Obtain y = yr (mod k) by disproof assumption and search series {n*k + 1} for an appropriate prime number
        if (dp_type == 1) {
            read_solution_v1();
            //If x >= dp_power, c ^ y = R (mod M).
            int R = read_solution_v1();
            int M = read_solution_v1();
            int yr = read_solution_v1();
            //However, c ^ y = R (mod M) is impossible.
            // e.g. 2 ^ x + 5 = 11 ^ y
            if (yr == -1) {
                // "/-"
                int string_fdgiat[3] = {47, 45, 10};
                print_line(string_fdgiat);
                // "(Class II, Back Mode, no magic prime)   %d ^ x + %d = %d ^ y"
                int string_ejsnvu[61] = {40, 67, 108, 97, 115, 115, 32, 73, 73, 44, 32, 66, 97, 99, 107, 32, 77, 111, 100, 101, 44, 32, 110, 111, 32, 109, 97, 103, 105, 99, 32, 112, 114, 105, 109, 101, 41, 32, 32, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 10};
                print_line_with_ddd(string_ejsnvu, a, b, c);
                print_solution_v1();
                // "-/"
                int string_bwbaxw[3] = {45, 47, 10};
                print_line(string_bwbaxw);
                // "theorem diophantine1_%d_%d_%d (x : Nat) (y : Nat) (h1 : x >= 1) (h2 : y >= 1) (h3 : %d ^ x + %d = %d ^ y) :"
                int string_ooskca[108] = {116, 104, 101, 111, 114, 101, 109, 32, 100, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 49, 95, 37, 100, 95, 37, 100, 95, 37, 100, 32, 40, 120, 32, 58, 32, 78, 97, 116, 41, 32, 40, 121, 32, 58, 32, 78, 97, 116, 41, 32, 40, 104, 49, 32, 58, 32, 120, 32, 62, 61, 32, 49, 41, 32, 40, 104, 50, 32, 58, 32, 121, 32, 62, 61, 32, 49, 41, 32, 40, 104, 51, 32, 58, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 41, 32, 58, 10};
                print_line_with_dddddd(string_ooskca, a, b, c, a, b, c);
                // "  "
                int string_iuqvxc[3] = {32, 32, 0};
                print_word(string_iuqvxc);
                print_Lean4_prop_v1(12, 0);
                print_line(newline);
                // "  := by"
                int string_vgpnki[8] = {32, 32, 58, 61, 32, 98, 121, 10};
                print_line(string_vgpnki);
                // "  have h4 : x % 1 = 0 := by omega"
                int string_iiencn[34] = {32, 32, 104, 97, 118, 101, 32, 104, 52, 32, 58, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
                print_line(string_iiencn);
                // "  have h5 : y % 1 = 0 := by omega"
                int string_xjsvvg[34] = {32, 32, 104, 97, 118, 101, 32, 104, 53, 32, 58, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
                print_line(string_xjsvvg);  
                // "  by_cases h6 : x >= %d"
                int string_dfptre[24] = {32, 32, 98, 121, 95, 99, 97, 115, 101, 115, 32, 104, 54, 32, 58, 32, 120, 32, 62, 61, 32, 37, 100, 10};
                print_line_with_d(string_dfptre, dp_power);
                // "  have h7 := Claim (%d ^ x \% %d = 0) ["
                int string_umttly[40] = {32, 32, 104, 97, 118, 101, 32, 104, 55, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 40, 37, 100, 32, 94, 32, 120, 32, 92, 37, 32, 37, 100, 32, 61, 32, 48, 41, 32, 91, 10};
                print_line_with_dd(string_umttly, a, M);   
                // "    {prop := x % 1 = 0, proof := h4},"
                int string_oqqwqd[38] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 52, 125, 44, 10};
                print_line(string_oqqwqd);
                // "    {prop := x >= %d, proof := h6},"
                int string_blhhbn[36] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 62, 61, 32, 37, 100, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 54, 125, 44, 10};
                print_line_with_d(string_blhhbn, dp_power);   
                // "  ] "pow_mod_eq_zero""
                int string_ilbvbw[22] = {32, 32, 93, 32, 34, 112, 111, 119, 95, 109, 111, 100, 95, 101, 113, 95, 122, 101, 114, 111, 34, 10};
                print_line(string_ilbvbw); 
                // "  have h8 : %d ^ y \% %d = %d := by omega"
                int string_wpnmou[42] = {32, 32, 104, 97, 118, 101, 32, 104, 56, 32, 58, 32, 37, 100, 32, 94, 32, 121, 32, 92, 37, 32, 37, 100, 32, 61, 32, 37, 100, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
                print_line_with_ddd(string_wpnmou, c, M, R);
                // "  have h9 := Claim False ["
                int string_xlvqim[27] = {32, 32, 104, 97, 118, 101, 32, 104, 57, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 70, 97, 108, 115, 101, 32, 91, 10};
                print_line(string_xlvqim);   
                // "    {prop := y % 1 = 0, proof := h5},"
                int string_dbcxis[38] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 53, 125, 44, 10};
                print_line(string_dbcxis);
                // "    {prop := y >= 1, proof := h2},"
                int string_neglln[35] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 50, 125, 44, 10};
                print_line(string_neglln);   
                // "    {prop := %d ^ y \% %d = %d, proof := h8},"
                int string_ejhkip[46] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 37, 100, 32, 94, 32, 121, 32, 92, 37, 32, 37, 100, 32, 61, 32, 37, 100, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 56, 125, 44, 10};
                print_line_with_ddd(string_ejhkip, c, M, R);
                // "  ] "observe_mod_cycle""
                int string_uqbcrh[24] = {32, 32, 93, 32, 34, 111, 98, 115, 101, 114, 118, 101, 95, 109, 111, 100, 95, 99, 121, 99, 108, 101, 34, 10};
                print_line(string_uqbcrh);
                // "  apply False.elim h9"
                int string_srxwip[22] = {32, 32, 97, 112, 112, 108, 121, 32, 70, 97, 108, 115, 101, 46, 101, 108, 105, 109, 32, 104, 57, 10};
                print_line(string_srxwip);
                // "  have h7 : x <= %d := by omega"
                int string_djzskp[32] = {32, 32, 104, 97, 118, 101, 32, 104, 55, 32, 58, 32, 120, 32, 60, 61, 32, 37, 100, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
                print_line_with_d(string_djzskp, dp_power-1);
                // "  have h8 := Claim "
                int string_yijuvr[20] = {32, 32, 104, 97, 118, 101, 32, 104, 56, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 0};
                print_word(string_yijuvr);
                print_Lean4_prop_v1(12, 1);
                // " ["
                int string_vtrnql[3] = {32, 91, 10};
                print_line(string_vtrnql);
                // "    {prop :=  x % 1 = 0, proof := h4},"
                int string_jjefym[39] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 52, 125, 44, 10};
                print_line(string_jjefym);
                // "    {prop :=  x >= 1, proof := h1},"
                int string_fdcvcu[36] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 120, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 49, 125, 44, 10};
                print_line(string_fdcvcu);
                // "    {prop :=  y % 1 = 0, proof := h5},"
                int string_vwaitd[39] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 53, 125, 44, 10};
                print_line(string_vwaitd);
                // "    {prop :=  y >= 1, proof := h2},"
                int string_jevuve[36] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 121, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 50, 125, 44, 10};
                print_line(string_jevuve);
                // "    {prop := %d ^ x + %d = %d ^ y, proof := h3},"
                int string_lkrglh[49] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 51, 125, 44, 10};
                print_line_with_ddd(string_lkrglh, a, b, c);
                // "    {prop := x <= %d, proof := h7},"
                int string_tlnivm[36] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 60, 61, 32, 37, 100, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 55, 125, 44, 10};
                print_line_with_d(string_tlnivm, dp_power-1);
                // "  ] "diophantine1_enumeration""
                int string_vjyzmh[31] = {32, 32, 93, 32, 34, 100, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 49, 95, 101, 110, 117, 109, 101, 114, 97, 116, 105, 111, 110, 34, 10};
                print_line(string_vjyzmh);
                // "  exact h8"
                int string_jnzvud[11] = {32, 32, 101, 120, 97, 99, 116, 32, 104, 56, 10};
                print_line(string_jnzvud);
            // c ^ y = R (mod M) => y = yr (mod k)
            // e.g. 2 ^ x + 1 = 17 ^ y
            }else{
                int k = read_solution_v1();
                int P = read_solution_v1(); // magic prime
                int m = read_solution_v1(); // y = yr (mod k) => y = y1, y2, ..., y_npossibilities (mod m)
                int npossibilities = read_solution_v1();
                int i = 0;
                while (i < npossibilities) {
                    read_solution_v1();
                    i = i + 1;
                }
                int pointer1 = solution_v1_pointer;
                read_solution_v1();
                i = 0;
                while (i < npossibilities) {
                    read_solution_v1();
                    i = i + 1;
                }
                read_solution_v1();
                int pointer2 = solution_v1_pointer;
                read_solution_v1();
                i = 0;
                while (i < npossibilities) {
                    read_solution_v1();
                    i = i + 1;
                }
                read_solution_v1();
                // "/-"
                int string_gqwocv[3] = {47, 45, 10};
                print_line(string_gqwocv);
                // "(Class II, Back Mode, with magic prime %d)   %d ^ x + %d = %d ^ y"
                int string_whthxd[66] = {40, 67, 108, 97, 115, 115, 32, 73, 73, 44, 32, 66, 97, 99, 107, 32, 77, 111, 100, 101, 44, 32, 119, 105, 116, 104, 32, 109, 97, 103, 105, 99, 32, 112, 114, 105, 109, 101, 32, 37, 100, 41, 32, 32, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 10};
                print_line_with_dddd(string_whthxd, P, a, b, c);
                print_solution_v1();
                // "-/"
                int string_lyflja[3] = {45, 47, 10};
                print_line(string_lyflja);
                // "theorem diophantine1_%d_%d_%d (x : Nat) (y : Nat) (h1 : x >= 1) (h2 : y >= 1) (h3 : %d ^ x + %d = %d ^ y) :"
                int string_bngzja[108] = {116, 104, 101, 111, 114, 101, 109, 32, 100, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 49, 95, 37, 100, 95, 37, 100, 95, 37, 100, 32, 40, 120, 32, 58, 32, 78, 97, 116, 41, 32, 40, 121, 32, 58, 32, 78, 97, 116, 41, 32, 40, 104, 49, 32, 58, 32, 120, 32, 62, 61, 32, 49, 41, 32, 40, 104, 50, 32, 58, 32, 121, 32, 62, 61, 32, 49, 41, 32, 40, 104, 51, 32, 58, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 41, 32, 58, 10};
                print_line_with_dddddd(string_bngzja, a, b, c, a, b, c);
                // "  "
                int string_yvqudh[3] = {32, 32, 0};
                print_word(string_yvqudh);
                print_Lean4_prop_v1(solution_v1_pointer, 0);
                print_line(newline);
                // "  := by"
                int string_vsdsla[8] = {32, 32, 58, 61, 32, 98, 121, 10};
                print_line(string_vsdsla);
                // "  have h4 : x % 1 = 0 := by omega"
                int string_cgvosn[34] = {32, 32, 104, 97, 118, 101, 32, 104, 52, 32, 58, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
                print_line(string_cgvosn);
                // "  have h5 : y % 1 = 0 := by omega"
                int string_chhbku[34] = {32, 32, 104, 97, 118, 101, 32, 104, 53, 32, 58, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
                print_line(string_chhbku);  
                // "  by_cases h6 : x >= %d"
                int string_lcxpan[24] = {32, 32, 98, 121, 95, 99, 97, 115, 101, 115, 32, 104, 54, 32, 58, 32, 120, 32, 62, 61, 32, 37, 100, 10};
                print_line_with_d(string_lcxpan, dp_power);
                // "  have h7 := Claim (%d ^ x \% %d = 0) ["
                int string_gdlpgk[40] = {32, 32, 104, 97, 118, 101, 32, 104, 55, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 40, 37, 100, 32, 94, 32, 120, 32, 92, 37, 32, 37, 100, 32, 61, 32, 48, 41, 32, 91, 10};
                print_line_with_dd(string_gdlpgk, a, M);   
                // "    {prop := x % 1 = 0, proof := h4},"
                int string_rczbnn[38] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 52, 125, 44, 10};
                print_line(string_rczbnn);
                // "    {prop := x >= %d, proof := h6},"
                int string_zokmqz[36] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 62, 61, 32, 37, 100, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 54, 125, 44, 10};
                print_line_with_d(string_zokmqz, dp_power);   
                // "  ] "pow_mod_eq_zero""
                int string_gauitq[22] = {32, 32, 93, 32, 34, 112, 111, 119, 95, 109, 111, 100, 95, 101, 113, 95, 122, 101, 114, 111, 34, 10};
                print_line(string_gauitq); 
                // "  have h8 : %d ^ y \% %d = %d := by omega"
                int string_utibov[42] = {32, 32, 104, 97, 118, 101, 32, 104, 56, 32, 58, 32, 37, 100, 32, 94, 32, 121, 32, 92, 37, 32, 37, 100, 32, 61, 32, 37, 100, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
                print_line_with_ddd(string_utibov, c, M, R);
                // "  have h9 := Claim (y \% %d = %d) ["
                int string_eumsqv[36] = {32, 32, 104, 97, 118, 101, 32, 104, 57, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 40, 121, 32, 92, 37, 32, 37, 100, 32, 61, 32, 37, 100, 41, 32, 91, 10};
                print_line_with_dd(string_eumsqv, k, yr);   
                // "    {prop := y % 1 = 0, proof := h5},"
                int string_bulhbf[38] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 53, 125, 44, 10};
                print_line(string_bulhbf);
                // "    {prop := y >= 1, proof := h2},"
                int string_bynzog[35] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 50, 125, 44, 10};
                print_line(string_bynzog);   
                // "    {prop := %d ^ y \% %d = %d, proof := h8},"
                int string_tejuwi[46] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 37, 100, 32, 94, 32, 121, 32, 92, 37, 32, 37, 100, 32, 61, 32, 37, 100, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 56, 125, 44, 10};
                print_line_with_ddd(string_tejuwi, c, M, R);
                // "  ] "observe_mod_cycle""
                int string_djxtxk[24] = {32, 32, 93, 32, 34, 111, 98, 115, 101, 114, 118, 101, 95, 109, 111, 100, 95, 99, 121, 99, 108, 101, 34, 10};
                print_line(string_djxtxk);

                // "  have h10 := Claim (List.Mem ("
                int string_zmmynu[32] = {32, 32, 104, 97, 118, 101, 32, 104, 49, 48, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 40, 76, 105, 115, 116, 46, 77, 101, 109, 32, 40, 0};
                print_word(string_zmmynu);
                putint(c);
                // " ^ y % "
                int string_scpvoi[8] = {32, 94, 32, 121, 32, 37, 32, 0};
                print_word(string_scpvoi);
                putint(P);
                // ") ["
                int string_crhplr[4] = {41, 32, 91, 0};
                print_word(string_crhplr);
                print_Lean4_int_array(pointer1);
                // "]) ["
                int string_jbwjzh[5] = {93, 41, 32, 91, 10};
                print_line(string_jbwjzh);
                // "    {prop := y % 1 = 0, proof := h5},"
                int string_zybqju[38] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 53, 125, 44, 10};
                print_line(string_zybqju);
                // "    {prop := y >= 1, proof := h2},"
                int string_rydpua[35] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 50, 125, 44, 10};
                print_line(string_rydpua);
                // "    {prop := y \% %d = %d, proof := h9},"
                int string_bujjop[41] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 92, 37, 32, 37, 100, 32, 61, 32, 37, 100, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 57, 125, 44, 10};
                print_line_with_dd(string_bujjop, k, yr);
                // "  ] "utilize_mod_cycle""
                int string_ryjton[24] = {32, 32, 93, 32, 34, 117, 116, 105, 108, 105, 122, 101, 95, 109, 111, 100, 95, 99, 121, 99, 108, 101, 34, 10};
                print_line(string_ryjton);

                // "  have h11 := Claim (List.Mem ("
                int string_kqgctm[32] = {32, 32, 104, 97, 118, 101, 32, 104, 49, 49, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 40, 76, 105, 115, 116, 46, 77, 101, 109, 32, 40, 0};
                print_word(string_kqgctm);
                putint(a);
                // " ^ x % "
                int string_kogglz[8] = {32, 94, 32, 120, 32, 37, 32, 0};
                print_word(string_kogglz);
                putint(P);
                // ") ["
                int string_hxmdwl[4] = {41, 32, 91, 0};
                print_word(string_hxmdwl);
                print_Lean4_int_array(pointer2);
                // "]) ["
                int string_xlcrvi[5] = {93, 41, 32, 91, 10};
                print_line(string_xlcrvi);          
                // "    {prop := List.Mem ("
                int string_jboxws[24] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 76, 105, 115, 116, 46, 77, 101, 109, 32, 40, 0};
                print_word(string_jboxws);
                putint(c);
                // " ^ y % "
                int string_yqundf[8] = {32, 94, 32, 121, 32, 37, 32, 0};
                print_word(string_yqundf);
                putint(P); 
                // ") ["
                int string_duaoju[4] = {41, 32, 91, 0};
                print_word(string_duaoju);
                print_Lean4_int_array(pointer1); 
                // "], proof := h10},"
                int string_opcizs[18] = {93, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 49, 48, 125, 44, 10};
                print_line(string_opcizs);
                // "    {prop := %d ^ x + %d = %d ^ y, proof := h3},"
                int string_ntvbzq[49] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 51, 125, 44, 10};
                print_line_with_ddd(string_ntvbzq, a, b, c);
                // "  ] "compute_mod_sub""
                int string_lriwuq[22] = {32, 32, 93, 32, 34, 99, 111, 109, 112, 117, 116, 101, 95, 109, 111, 100, 95, 115, 117, 98, 34, 10};
                print_line(string_lriwuq);

                // "  have h12 := Claim False ["
                int string_ezlxbd[28] = {32, 32, 104, 97, 118, 101, 32, 104, 49, 50, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 70, 97, 108, 115, 101, 32, 91, 10};
                print_line(string_ezlxbd);
                // "    {prop := x % 1 = 0, proof := h4},"
                int string_deisiy[38] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 52, 125, 44, 10};
                print_line(string_deisiy);
                // "    {prop := x >= 1, proof := h1},"
                int string_xvgqod[35] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 49, 125, 44, 10};
                print_line(string_xvgqod);
                // "    {prop := List.Mem ("
                int string_hnneye[24] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 76, 105, 115, 116, 46, 77, 101, 109, 32, 40, 0};
                print_word(string_hnneye);
                putint(a);
                // " ^ x % "
                int string_rspvov[8] = {32, 94, 32, 120, 32, 37, 32, 0};
                print_word(string_rspvov);
                putint(P);
                // ") ["
                int string_abqoqt[4] = {41, 32, 91, 0};
                print_word(string_abqoqt);
                print_Lean4_int_array(pointer2);
                // "], proof := h11},"
                int string_kqmqhy[18] = {93, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 49, 49, 125, 44, 10};
                print_line(string_kqmqhy);
                // "  ] "exhaust_mod_cycle""
                int string_murhbb[24] = {32, 32, 93, 32, 34, 101, 120, 104, 97, 117, 115, 116, 95, 109, 111, 100, 95, 99, 121, 99, 108, 101, 34, 10};
                print_line(string_murhbb);

                // "  apply False.elim h12"
                int string_lmfpis[23] = {32, 32, 97, 112, 112, 108, 121, 32, 70, 97, 108, 115, 101, 46, 101, 108, 105, 109, 32, 104, 49, 50, 10};
                print_line(string_lmfpis);
                // "  have h7 : x <= %d := by omega"
                int string_twzdjo[32] = {32, 32, 104, 97, 118, 101, 32, 104, 55, 32, 58, 32, 120, 32, 60, 61, 32, 37, 100, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
                print_line_with_d(string_twzdjo, dp_power-1);
                // "  have h8 := Claim "
                int string_imggch[20] = {32, 32, 104, 97, 118, 101, 32, 104, 56, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 0};
                print_word(string_imggch);
                print_Lean4_prop_v1(solution_v1_pointer, 1);
                // " ["
                int string_jpgwei[3] = {32, 91, 10};
                print_line(string_jpgwei);
                // "    {prop :=  x % 1 = 0, proof := h4},"
                int string_pitmnm[39] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 52, 125, 44, 10};
                print_line(string_pitmnm);
                // "    {prop :=  x >= 1, proof := h1},"
                int string_iaynzf[36] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 120, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 49, 125, 44, 10};
                print_line(string_iaynzf);
                // "    {prop :=  y % 1 = 0, proof := h5},"
                int string_jbmwrm[39] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 53, 125, 44, 10};
                print_line(string_jbmwrm);
                // "    {prop :=  y >= 1, proof := h2},"
                int string_nwlwst[36] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 121, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 50, 125, 44, 10};
                print_line(string_nwlwst);
                // "    {prop := %d ^ x + %d = %d ^ y, proof := h3},"
                int string_jkofob[49] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 51, 125, 44, 10};
                print_line_with_ddd(string_jkofob, a, b, c);
                // "    {prop := x <= %d, proof := h7},"
                int string_nthzrd[36] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 60, 61, 32, 37, 100, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 55, 125, 44, 10};
                print_line_with_d(string_nthzrd, dp_power-1);
                // "  ] "diophantine1_enumeration""
                int string_zkuiyt[31] = {32, 32, 93, 32, 34, 100, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 49, 95, 101, 110, 117, 109, 101, 114, 97, 116, 105, 111, 110, 34, 10};
                print_line(string_zkuiyt);
                // "  exact h8"
                int string_fnnbdi[11] = {32, 32, 101, 120, 97, 99, 116, 32, 104, 56, 10};
                print_line(string_fnnbdi);
            }
        // Front Mode: Obtain x = xr (mod k) by disproof assumption and search series {n*k + 1} for an appropriate prime number
        }else if (dp_type == 2) {
            read_solution_v1();
            //If y >= dp_power, a ^ x = R (mod M).
            int R = read_solution_v1();
            int M = read_solution_v1();
            int xr = read_solution_v1();
            //However, a ^ x = R (mod M) is impossible.
            // e.g. 2 ^ x + 9 = 7 ^ y
            if (xr == -1) {
                // "/-"
                int string_mlpnip[3] = {47, 45, 10};
                print_line(string_mlpnip);
                // "(Class II, Front Mode, no magic prime)   %d ^ x + %d = %d ^ y"
                int string_ezthiv[62] = {40, 67, 108, 97, 115, 115, 32, 73, 73, 44, 32, 70, 114, 111, 110, 116, 32, 77, 111, 100, 101, 44, 32, 110, 111, 32, 109, 97, 103, 105, 99, 32, 112, 114, 105, 109, 101, 41, 32, 32, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 10};
                print_line_with_ddd(string_ezthiv, a, b, c);
                print_solution_v1();
                // "-/"
                int string_nshvjr[3] = {45, 47, 10};
                print_line(string_nshvjr);
                // "theorem diophantine1_%d_%d_%d (x : Nat) (y : Nat) (h1 : x >= 1) (h2 : y >= 1) (h3 : %d ^ x + %d = %d ^ y) :"
                int string_zpusra[108] = {116, 104, 101, 111, 114, 101, 109, 32, 100, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 49, 95, 37, 100, 95, 37, 100, 95, 37, 100, 32, 40, 120, 32, 58, 32, 78, 97, 116, 41, 32, 40, 121, 32, 58, 32, 78, 97, 116, 41, 32, 40, 104, 49, 32, 58, 32, 120, 32, 62, 61, 32, 49, 41, 32, 40, 104, 50, 32, 58, 32, 121, 32, 62, 61, 32, 49, 41, 32, 40, 104, 51, 32, 58, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 41, 32, 58, 10};
                print_line_with_dddddd(string_zpusra, a, b, c, a, b, c);
                // "  "
                int string_mzuups[3] = {32, 32, 0};
                print_word(string_mzuups);
                print_Lean4_prop_v1(12, 0);
                print_line(newline);
                // "  := by"
                int string_peqqvd[8] = {32, 32, 58, 61, 32, 98, 121, 10};
                print_line(string_peqqvd);
                // "  have h4 : x % 1 = 0 := by omega"
                int string_raycai[34] = {32, 32, 104, 97, 118, 101, 32, 104, 52, 32, 58, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
                print_line(string_raycai);
                // "  have h5 : y % 1 = 0 := by omega"
                int string_drkuxw[34] = {32, 32, 104, 97, 118, 101, 32, 104, 53, 32, 58, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
                print_line(string_drkuxw);  
                // "  by_cases h6 : y >= %d"
                int string_tbdfir[24] = {32, 32, 98, 121, 95, 99, 97, 115, 101, 115, 32, 104, 54, 32, 58, 32, 121, 32, 62, 61, 32, 37, 100, 10};
                print_line_with_d(string_tbdfir, dp_power);
                // "  have h7 := Claim (%d ^ y \% %d = 0) ["
                int string_niexij[40] = {32, 32, 104, 97, 118, 101, 32, 104, 55, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 40, 37, 100, 32, 94, 32, 121, 32, 92, 37, 32, 37, 100, 32, 61, 32, 48, 41, 32, 91, 10};
                print_line_with_dd(string_niexij, c, M);   
                // "    {prop := y % 1 = 0, proof := h5},"
                int string_usqspe[38] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 53, 125, 44, 10};
                print_line(string_usqspe);
                // "    {prop := y >= %d, proof := h6},"
                int string_gofzhh[36] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 62, 61, 32, 37, 100, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 54, 125, 44, 10};
                print_line_with_d(string_gofzhh, dp_power);   
                // "  ] "pow_mod_eq_zero""
                int string_fsijyu[22] = {32, 32, 93, 32, 34, 112, 111, 119, 95, 109, 111, 100, 95, 101, 113, 95, 122, 101, 114, 111, 34, 10};
                print_line(string_fsijyu); 
                // "  have h8 : %d ^ x \% %d = %d := by omega"
                int string_hdrjzv[42] = {32, 32, 104, 97, 118, 101, 32, 104, 56, 32, 58, 32, 37, 100, 32, 94, 32, 120, 32, 92, 37, 32, 37, 100, 32, 61, 32, 37, 100, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
                print_line_with_ddd(string_hdrjzv, a, M, R);
                // "  have h9 := Claim False ["
                int string_yuhhsj[27] = {32, 32, 104, 97, 118, 101, 32, 104, 57, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 70, 97, 108, 115, 101, 32, 91, 10};
                print_line(string_yuhhsj);   
                // "    {prop := x % 1 = 0, proof := h4},"
                int string_lgmfoy[38] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 52, 125, 44, 10};
                print_line(string_lgmfoy);
                // "    {prop := x >= 1, proof := h1},"
                int string_sdqpgr[35] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 49, 125, 44, 10};
                print_line(string_sdqpgr);   
                // "    {prop := %d ^ x \% %d = %d, proof := h8},"
                int string_nqbksc[46] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 37, 100, 32, 94, 32, 120, 32, 92, 37, 32, 37, 100, 32, 61, 32, 37, 100, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 56, 125, 44, 10};
                print_line_with_ddd(string_nqbksc, a, M, R);
                // "  ] "observe_mod_cycle""
                int string_uaoyky[24] = {32, 32, 93, 32, 34, 111, 98, 115, 101, 114, 118, 101, 95, 109, 111, 100, 95, 99, 121, 99, 108, 101, 34, 10};
                print_line(string_uaoyky);
                // "  apply False.elim h9"
                int string_wmfziq[22] = {32, 32, 97, 112, 112, 108, 121, 32, 70, 97, 108, 115, 101, 46, 101, 108, 105, 109, 32, 104, 57, 10};
                print_line(string_wmfziq);
                // "  have h7 : y <= %d := by omega"
                int string_xconsy[32] = {32, 32, 104, 97, 118, 101, 32, 104, 55, 32, 58, 32, 121, 32, 60, 61, 32, 37, 100, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
                print_line_with_d(string_xconsy, dp_power-1);
                // "  have h8 := Claim "
                int string_xewexz[20] = {32, 32, 104, 97, 118, 101, 32, 104, 56, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 0};
                print_word(string_xewexz);
                                print_Lean4_prop_v1(12, 1);
                // " ["
                int string_kmyzyw[3] = {32, 91, 10};
                print_line(string_kmyzyw);
                // "    {prop :=  x % 1 = 0, proof := h4},"
                int string_aoczhz[39] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 52, 125, 44, 10};
                print_line(string_aoczhz);
                // "    {prop :=  x >= 1, proof := h1},"
                int string_omywmf[36] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 120, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 49, 125, 44, 10};
                print_line(string_omywmf);
                // "    {prop :=  y % 1 = 0, proof := h5},"
                int string_celget[39] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 53, 125, 44, 10};
                print_line(string_celget);
                // "    {prop :=  y >= 1, proof := h2},"
                int string_uotewx[36] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 121, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 50, 125, 44, 10};
                print_line(string_uotewx);
                // "    {prop := %d ^ x + %d = %d ^ y, proof := h3},"
                int string_vncred[49] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 51, 125, 44, 10};
                print_line_with_ddd(string_vncred, a, b, c);
                // "    {prop := y <= %d, proof := h7},"
                int string_igggty[36] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 60, 61, 32, 37, 100, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 55, 125, 44, 10};
                print_line_with_d(string_igggty, dp_power-1);
                // "  ] "diophantine1_enumeration""
                int string_hsaqsb[31] = {32, 32, 93, 32, 34, 100, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 49, 95, 101, 110, 117, 109, 101, 114, 97, 116, 105, 111, 110, 34, 10};
                print_line(string_hsaqsb);
                // "  exact h8"
                int string_dhknxs[11] = {32, 32, 101, 120, 97, 99, 116, 32, 104, 56, 10};
                print_line(string_dhknxs);
            // a ^ x = R (mod M) => x = xr (mod k)
            // e.g. 2 ^ x + 1 = 3 ^ y
            }else{
                int k = read_solution_v1();
                int P = read_solution_v1(); // magic prime
                int m = read_solution_v1(); // x = xr (mod k) => x = x1, x2, ..., x_npossibilities (mod m)
                int npossibilities = read_solution_v1();
                int i = 0;
                while (i < npossibilities) {
                    read_solution_v1();
                    i = i + 1;
                }
                int pointer1 = solution_v1_pointer;
                read_solution_v1();
                i = 0;
                while (i < npossibilities) {
                    read_solution_v1();
                    i = i + 1;
                }
                read_solution_v1();
                int pointer2 = solution_v1_pointer;
                read_solution_v1();
                i = 0;
                while (i < npossibilities) {
                    read_solution_v1();
                    i = i + 1;
                }
                read_solution_v1();
                // "/-"
                int string_idxhpf[3] = {47, 45, 10};
                print_line(string_idxhpf);
                // "(Class II, Front Mode, with magic prime %d)   %d ^ x + %d = %d ^ y"
                int string_ddtpko[67] = {40, 67, 108, 97, 115, 115, 32, 73, 73, 44, 32, 70, 114, 111, 110, 116, 32, 77, 111, 100, 101, 44, 32, 119, 105, 116, 104, 32, 109, 97, 103, 105, 99, 32, 112, 114, 105, 109, 101, 32, 37, 100, 41, 32, 32, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 10};
                print_line_with_dddd(string_ddtpko, P, a, b, c);
                print_solution_v1();
                // "-/"
                int string_mnrfgt[3] = {45, 47, 10};
                print_line(string_mnrfgt);
                // "theorem diophantine1_%d_%d_%d (x : Nat) (y : Nat) (h1 : x >= 1) (h2 : y >= 1) (h3 : %d ^ x + %d = %d ^ y) :"
                int string_wclsco[108] = {116, 104, 101, 111, 114, 101, 109, 32, 100, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 49, 95, 37, 100, 95, 37, 100, 95, 37, 100, 32, 40, 120, 32, 58, 32, 78, 97, 116, 41, 32, 40, 121, 32, 58, 32, 78, 97, 116, 41, 32, 40, 104, 49, 32, 58, 32, 120, 32, 62, 61, 32, 49, 41, 32, 40, 104, 50, 32, 58, 32, 121, 32, 62, 61, 32, 49, 41, 32, 40, 104, 51, 32, 58, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 41, 32, 58, 10};
                print_line_with_dddddd(string_wclsco, a, b, c, a, b, c);
                // "  "
                int string_bonodi[3] = {32, 32, 0};
                print_word(string_bonodi);
                print_Lean4_prop_v1(solution_v1_pointer, 0);
                print_line(newline);
                // "  := by"
                int string_ndfpcn[8] = {32, 32, 58, 61, 32, 98, 121, 10};
                print_line(string_ndfpcn);
                // "  have h4 : x % 1 = 0 := by omega"
                int string_vlnlbm[34] = {32, 32, 104, 97, 118, 101, 32, 104, 52, 32, 58, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
                print_line(string_vlnlbm);
                // "  have h5 : y % 1 = 0 := by omega"
                int string_uskvtp[34] = {32, 32, 104, 97, 118, 101, 32, 104, 53, 32, 58, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
                print_line(string_uskvtp);  
                // "  by_cases h6 : y >= %d"
                int string_bibzyb[24] = {32, 32, 98, 121, 95, 99, 97, 115, 101, 115, 32, 104, 54, 32, 58, 32, 121, 32, 62, 61, 32, 37, 100, 10};
                print_line_with_d(string_bibzyb, dp_power);
                // "  have h7 := Claim (%d ^ y \% %d = 0) ["
                int string_yakttz[40] = {32, 32, 104, 97, 118, 101, 32, 104, 55, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 40, 37, 100, 32, 94, 32, 121, 32, 92, 37, 32, 37, 100, 32, 61, 32, 48, 41, 32, 91, 10};
                print_line_with_dd(string_yakttz, c, M);   
                // "    {prop := y % 1 = 0, proof := h5},"
                int string_qkzjwx[38] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 53, 125, 44, 10};
                print_line(string_qkzjwx);
                // "    {prop := y >= %d, proof := h6},"
                int string_jrroqj[36] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 62, 61, 32, 37, 100, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 54, 125, 44, 10};
                print_line_with_d(string_jrroqj, dp_power);   
                // "  ] "pow_mod_eq_zero""
                int string_ennsfa[22] = {32, 32, 93, 32, 34, 112, 111, 119, 95, 109, 111, 100, 95, 101, 113, 95, 122, 101, 114, 111, 34, 10};
                print_line(string_ennsfa); 
                // "  have h8 : %d ^ x \% %d = %d := by omega"
                int string_ahronv[42] = {32, 32, 104, 97, 118, 101, 32, 104, 56, 32, 58, 32, 37, 100, 32, 94, 32, 120, 32, 92, 37, 32, 37, 100, 32, 61, 32, 37, 100, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
                print_line_with_ddd(string_ahronv, a, M, R);
                // "  have h9 := Claim (x \% %d = %d) ["
                int string_gjhysc[36] = {32, 32, 104, 97, 118, 101, 32, 104, 57, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 40, 120, 32, 92, 37, 32, 37, 100, 32, 61, 32, 37, 100, 41, 32, 91, 10};
                print_line_with_dd(string_gjhysc, k, xr);   
                // "    {prop := x % 1 = 0, proof := h4},"
                int string_vktwaf[38] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 52, 125, 44, 10};
                print_line(string_vktwaf);
                // "    {prop := x >= 1, proof := h1},"
                int string_capsbt[35] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 49, 125, 44, 10};
                print_line(string_capsbt);   
                // "    {prop := %d ^ x \% %d = %d, proof := h8},"
                int string_kgfwbn[46] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 37, 100, 32, 94, 32, 120, 32, 92, 37, 32, 37, 100, 32, 61, 32, 37, 100, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 56, 125, 44, 10};
                print_line_with_ddd(string_kgfwbn, a, M, R);
                // "  ] "observe_mod_cycle""
                int string_hvtipr[24] = {32, 32, 93, 32, 34, 111, 98, 115, 101, 114, 118, 101, 95, 109, 111, 100, 95, 99, 121, 99, 108, 101, 34, 10};
                print_line(string_hvtipr);

                // "  have h10 := Claim (List.Mem ("
                int string_ihdrfh[32] = {32, 32, 104, 97, 118, 101, 32, 104, 49, 48, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 40, 76, 105, 115, 116, 46, 77, 101, 109, 32, 40, 0};
                print_word(string_ihdrfh);
                putint(a);
                // " ^ x % "
                int string_bywxql[8] = {32, 94, 32, 120, 32, 37, 32, 0};
                print_word(string_bywxql);
                putint(P);
                // ") ["
                int string_mzyrui[4] = {41, 32, 91, 0};
                print_word(string_mzyrui);
                print_Lean4_int_array(pointer1);
                // "]) ["
                int string_kdjtmw[5] = {93, 41, 32, 91, 10};
                print_line(string_kdjtmw);
                // "    {prop := x % 1 = 0, proof := h4},"
                int string_hsuxoz[38] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 52, 125, 44, 10};
                print_line(string_hsuxoz);
                // "    {prop := x >= 1, proof := h1},"
                int string_odgfqx[35] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 49, 125, 44, 10};
                print_line(string_odgfqx);
                // "    {prop := x \% %d = %d, proof := h9},"
                int string_wcsegr[41] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 120, 32, 92, 37, 32, 37, 100, 32, 61, 32, 37, 100, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 57, 125, 44, 10};
                print_line_with_dd(string_wcsegr, k, xr);
                // "  ] "utilize_mod_cycle""
                int string_pwetso[24] = {32, 32, 93, 32, 34, 117, 116, 105, 108, 105, 122, 101, 95, 109, 111, 100, 95, 99, 121, 99, 108, 101, 34, 10};
                print_line(string_pwetso);

                // "  have h11 := Claim (List.Mem ("
                int string_mwiyay[32] = {32, 32, 104, 97, 118, 101, 32, 104, 49, 49, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 40, 76, 105, 115, 116, 46, 77, 101, 109, 32, 40, 0};
                print_word(string_mwiyay);
                putint(c);
                // " ^ y % "
                int string_zdzmgp[8] = {32, 94, 32, 121, 32, 37, 32, 0};
                print_word(string_zdzmgp);
                putint(P);
                // ") ["
                int string_fxoujn[4] = {41, 32, 91, 0};
                print_word(string_fxoujn);
                print_Lean4_int_array(pointer2);
                // "]) ["
                int string_jgnmcz[5] = {93, 41, 32, 91, 10};
                print_line(string_jgnmcz);          
                // "    {prop := List.Mem ("
                int string_mvxjko[24] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 76, 105, 115, 116, 46, 77, 101, 109, 32, 40, 0};
                print_word(string_mvxjko);
                putint(a);
                // " ^ x % "
                int string_fdgypk[8] = {32, 94, 32, 120, 32, 37, 32, 0};
                print_word(string_fdgypk);
                putint(P); 
                // ") ["
                int string_dijvmr[4] = {41, 32, 91, 0};
                print_word(string_dijvmr);
                print_Lean4_int_array(pointer1); 
                // "], proof := h10},"
                int string_rgvzqm[18] = {93, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 49, 48, 125, 44, 10};
                print_line(string_rgvzqm);
                // "    {prop := %d ^ x + %d = %d ^ y, proof := h3},"
                int string_euesmx[49] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 51, 125, 44, 10};
                print_line_with_ddd(string_euesmx, a, b, c);
                // "  ] "compute_mod_add""
                int string_oqbawy[22] = {32, 32, 93, 32, 34, 99, 111, 109, 112, 117, 116, 101, 95, 109, 111, 100, 95, 97, 100, 100, 34, 10};
                print_line(string_oqbawy);

                // "  have h12 := Claim False ["
                int string_rtkvgs[28] = {32, 32, 104, 97, 118, 101, 32, 104, 49, 50, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 70, 97, 108, 115, 101, 32, 91, 10};
                print_line(string_rtkvgs);
                // "    {prop := y % 1 = 0, proof := h5},"
                int string_anjqrq[38] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 53, 125, 44, 10};
                print_line(string_anjqrq);
                // "    {prop := y >= 1, proof := h2},"
                int string_mmaoan[35] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 50, 125, 44, 10};
                print_line(string_mmaoan);
                // "    {prop := List.Mem ("
                int string_hzavru[24] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 76, 105, 115, 116, 46, 77, 101, 109, 32, 40, 0};
                print_word(string_hzavru);
                putint(c);
                // " ^ y % "
                int string_xccden[8] = {32, 94, 32, 121, 32, 37, 32, 0};
                print_word(string_xccden);
                putint(P);
                // ") ["
                int string_vgkjko[4] = {41, 32, 91, 0};
                print_word(string_vgkjko);
                print_Lean4_int_array(pointer2);
                // "], proof := h11},"
                int string_zfrwqw[18] = {93, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 49, 49, 125, 44, 10};
                print_line(string_zfrwqw);
                // "  ] "exhaust_mod_cycle""
                int string_tcjoba[24] = {32, 32, 93, 32, 34, 101, 120, 104, 97, 117, 115, 116, 95, 109, 111, 100, 95, 99, 121, 99, 108, 101, 34, 10};
                print_line(string_tcjoba);

                // "  apply False.elim h12"
                int string_emluow[23] = {32, 32, 97, 112, 112, 108, 121, 32, 70, 97, 108, 115, 101, 46, 101, 108, 105, 109, 32, 104, 49, 50, 10};
                print_line(string_emluow);
                // "  have h7 : y <= %d := by omega"
                int string_cnbfwx[32] = {32, 32, 104, 97, 118, 101, 32, 104, 55, 32, 58, 32, 121, 32, 60, 61, 32, 37, 100, 32, 58, 61, 32, 98, 121, 32, 111, 109, 101, 103, 97, 10};
                print_line_with_d(string_cnbfwx, dp_power-1);
                // "  have h8 := Claim "
                int string_mbbyxo[20] = {32, 32, 104, 97, 118, 101, 32, 104, 56, 32, 58, 61, 32, 67, 108, 97, 105, 109, 32, 0};
                print_word(string_mbbyxo);
                print_Lean4_prop_v1(solution_v1_pointer, 1);
                // " ["
                int string_ayiypt[3] = {32, 91, 10};
                print_line(string_ayiypt);
                // "    {prop :=  x % 1 = 0, proof := h4},"
                int string_skcegv[39] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 120, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 52, 125, 44, 10};
                print_line(string_skcegv);
                // "    {prop :=  x >= 1, proof := h1},"
                int string_kxitdz[36] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 120, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 49, 125, 44, 10};
                print_line(string_kxitdz);
                // "    {prop :=  y % 1 = 0, proof := h5},"
                int string_snzblv[39] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 121, 32, 37, 32, 49, 32, 61, 32, 48, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 53, 125, 44, 10};
                print_line(string_snzblv);
                // "    {prop :=  y >= 1, proof := h2},"
                int string_itykua[36] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 32, 121, 32, 62, 61, 32, 49, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 50, 125, 44, 10};
                print_line(string_itykua);
                // "    {prop := %d ^ x + %d = %d ^ y, proof := h3},"
                int string_hzmjyl[49] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 37, 100, 32, 94, 32, 120, 32, 43, 32, 37, 100, 32, 61, 32, 37, 100, 32, 94, 32, 121, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 51, 125, 44, 10};
                print_line_with_ddd(string_hzmjyl, a, b, c);
                // "    {prop := y <= %d, proof := h7},"
                int string_rrcqus[36] = {32, 32, 32, 32, 123, 112, 114, 111, 112, 32, 58, 61, 32, 121, 32, 60, 61, 32, 37, 100, 44, 32, 112, 114, 111, 111, 102, 32, 58, 61, 32, 104, 55, 125, 44, 10};
                print_line_with_d(string_rrcqus, dp_power-1);
                // "  ] "diophantine1_enumeration""
                int string_cesqti[31] = {32, 32, 93, 32, 34, 100, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 49, 95, 101, 110, 117, 109, 101, 114, 97, 116, 105, 111, 110, 34, 10};
                print_line(string_cesqti);
                // "  exact h8"
                int string_caijhd[11] = {32, 32, 101, 120, 97, 99, 116, 32, 104, 56, 10};
                print_line(string_caijhd); 
            } 
        }else{
            // "-- [Solver V1] solution vector format is incorrect for unknown reason!"
            int array_elokaj[71] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 115, 111, 108, 117, 116, 105, 111, 110, 32, 118, 101, 99, 116, 111, 114, 32, 102, 111, 114, 109, 97, 116, 32, 105, 115, 32, 105, 110, 99, 111, 114, 114, 101, 99, 116, 32, 102, 111, 114, 32, 117, 110, 107, 110, 111, 119, 110, 32, 114, 101, 97, 115, 111, 110, 33, 10};
            assert(0, array_elokaj);
            if (!assertion) return;
        }
    }else{
        // "-- [Solver V1] solution vector format is incorrect for unknown reason!"
        int array_cpikhk[71] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 115, 111, 108, 117, 116, 105, 111, 110, 32, 118, 101, 99, 116, 111, 114, 32, 102, 111, 114, 109, 97, 116, 32, 105, 115, 32, 105, 110, 99, 111, 114, 114, 101, 99, 116, 32, 102, 111, 114, 32, 117, 110, 107, 110, 111, 119, 110, 32, 114, 101, 97, 115, 111, 110, 33, 10};
        assert(0, array_cpikhk);
        if (!assertion) return;
    }
}

// ------------------------------ api section ------------------------------

void generate_Claim_Structure() {
    // "-- Claim Structure"
    int string_zqorvu[19] = {45, 45, 32, 67, 108, 97, 105, 109, 32, 83, 116, 114, 117, 99, 116, 117, 114, 101, 10};
    print_line(string_zqorvu);
    // "structure VerifiedFact where"
    int string_faigfy[29] = {115, 116, 114, 117, 99, 116, 117, 114, 101, 32, 86, 101, 114, 105, 102, 105, 101, 100, 70, 97, 99, 116, 32, 119, 104, 101, 114, 101, 10};
    print_line(string_faigfy);
    // "  prop : Prop"
    int string_wirkxl[14] = {32, 32, 112, 114, 111, 112, 32, 58, 32, 80, 114, 111, 112, 10};
    print_line(string_wirkxl);
    // "  proof : prop"
    int string_ggogpx[15] = {32, 32, 112, 114, 111, 111, 102, 32, 58, 32, 112, 114, 111, 112, 10};
    print_line(string_ggogpx);
    print_line(newline);
    // "axiom Claim (prop_to_claim : Prop)"
    int string_kfzncb[35] = {97, 120, 105, 111, 109, 32, 67, 108, 97, 105, 109, 32, 40, 112, 114, 111, 112, 95, 116, 111, 95, 99, 108, 97, 105, 109, 32, 58, 32, 80, 114, 111, 112, 41, 10};
    print_line(string_kfzncb);
    // "  (verified_facts : List VerifiedFact)"
    int string_cqukbj[39] = {32, 32, 40, 118, 101, 114, 105, 102, 105, 101, 100, 95, 102, 97, 99, 116, 115, 32, 58, 32, 76, 105, 115, 116, 32, 86, 101, 114, 105, 102, 105, 101, 100, 70, 97, 99, 116, 41, 10};
    print_line(string_cqukbj);
    // "  (revalidator : String)"
    int string_znzwas[25] = {32, 32, 40, 114, 101, 118, 97, 108, 105, 100, 97, 116, 111, 114, 32, 58, 32, 83, 116, 114, 105, 110, 103, 41, 10};
    print_line(string_znzwas);
    // "  : prop_to_claim"
    int string_rngqcl[18] = {32, 32, 58, 32, 112, 114, 111, 112, 95, 116, 111, 95, 99, 108, 97, 105, 109, 10};
    print_line(string_rngqcl);
}


void Solve_Diophantine1_generate_Lean4_code(int a, int b, int c) {
    set_abc_v1(a, b, c);
    if (!assertion) return;
    Solve_Diophantine1();
    if(!assertion) return;
    if (solver_v1_success) {
        generate_Lean4_code_v1();
        if(!assertion) return;
    }else{
        // "-- [Solver V1] solver failed!"
        int string_lywgne[30] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 115, 111, 108, 118, 101, 114, 32, 102, 97, 105, 108, 101, 100, 33, 10};
        print_line(string_lywgne);
    }
}


void Solve_Diophantine1_backdoor() {
    max_trial_num_v1 = getint();
    mod_threshold_v1 = getint();
    hijack_settings = 1;
}


void Solve_Diophantine1_info() {
    // "[Diophantine Help Information]"
    int string_xwhqpd[31] = {91, 68, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 32, 72, 101, 108, 112, 32, 73, 110, 102, 111, 114, 109, 97, 116, 105, 111, 110, 93, 10};
    print_line(string_xwhqpd);
    // "Run the executable and"
    int string_tounai[23] = {82, 117, 110, 32, 116, 104, 101, 32, 101, 120, 101, 99, 117, 116, 97, 98, 108, 101, 32, 97, 110, 100, 10};
    print_line(string_tounai);
    // "0. Enter 0 to display this help information."
    int string_aywvhb[45] = {48, 46, 32, 69, 110, 116, 101, 114, 32, 48, 32, 116, 111, 32, 100, 105, 115, 112, 108, 97, 121, 32, 116, 104, 105, 115, 32, 104, 101, 108, 112, 32, 105, 110, 102, 111, 114, 109, 97, 116, 105, 111, 110, 46, 10};
    print_line(string_aywvhb);
    // "1. Enter 1 to launch an interactive shell; follow the prompts to input a, b, and c for solving."
    int string_wycmbt[96] = {49, 46, 32, 69, 110, 116, 101, 114, 32, 49, 32, 116, 111, 32, 108, 97, 117, 110, 99, 104, 32, 97, 110, 32, 105, 110, 116, 101, 114, 97, 99, 116, 105, 118, 101, 32, 115, 104, 101, 108, 108, 59, 32, 102, 111, 108, 108, 111, 119, 32, 116, 104, 101, 32, 112, 114, 111, 109, 112, 116, 115, 32, 116, 111, 32, 105, 110, 112, 117, 116, 32, 97, 44, 32, 98, 44, 32, 97, 110, 100, 32, 99, 32, 102, 111, 114, 32, 115, 111, 108, 118, 105, 110, 103, 46, 10};
    print_line(string_wycmbt);
    // "2. Enter 2 to start silent mode (for research use); input a_max a_min b_max b_min c_max c_min in order."
    int string_tdmogw[104] = {50, 46, 32, 69, 110, 116, 101, 114, 32, 50, 32, 116, 111, 32, 115, 116, 97, 114, 116, 32, 115, 105, 108, 101, 110, 116, 32, 109, 111, 100, 101, 32, 40, 102, 111, 114, 32, 114, 101, 115, 101, 97, 114, 99, 104, 32, 117, 115, 101, 41, 59, 32, 105, 110, 112, 117, 116, 32, 97, 95, 109, 97, 120, 32, 97, 95, 109, 105, 110, 32, 98, 95, 109, 97, 120, 32, 98, 95, 109, 105, 110, 32, 99, 95, 109, 97, 120, 32, 99, 95, 109, 105, 110, 32, 105, 110, 32, 111, 114, 100, 101, 114, 46, 10};
    print_line(string_tdmogw);
    // "3. Enter 3 to view the Lean formalization file `transcendental_diophantine1.lean`; it is recommended to redirect the output to a file, as the content is very long."
    int string_lfosfi[164] = {51, 46, 32, 69, 110, 116, 101, 114, 32, 51, 32, 116, 111, 32, 118, 105, 101, 119, 32, 116, 104, 101, 32, 76, 101, 97, 110, 32, 102, 111, 114, 109, 97, 108, 105, 122, 97, 116, 105, 111, 110, 32, 102, 105, 108, 101, 32, 96, 116, 114, 97, 110, 115, 99, 101, 110, 100, 101, 110, 116, 97, 108, 95, 100, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 49, 46, 108, 101, 97, 110, 96, 59, 32, 105, 116, 32, 105, 115, 32, 114, 101, 99, 111, 109, 109, 101, 110, 100, 101, 100, 32, 116, 111, 32, 114, 101, 100, 105, 114, 101, 99, 116, 32, 116, 104, 101, 32, 111, 117, 116, 112, 117, 116, 32, 116, 111, 32, 97, 32, 102, 105, 108, 101, 44, 32, 97, 115, 32, 116, 104, 101, 32, 99, 111, 110, 116, 101, 110, 116, 32, 105, 115, 32, 118, 101, 114, 121, 32, 108, 111, 110, 103, 46, 10};
    print_line(string_lfosfi);
}


void Solve_Diophantine1_shell() {
    
    set_xy_name_v1(string_x, string_y, strlen_x, strlen_y);
    // "Now solving diophantine equation a ^ x + b = c ^ y for its positive integer solutions (x, y)."
    int string_zqlndf[94] = {78, 111, 119, 32, 115, 111, 108, 118, 105, 110, 103, 32, 100, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 32, 101, 113, 117, 97, 116, 105, 111, 110, 32, 97, 32, 94, 32, 120, 32, 43, 32, 98, 32, 61, 32, 99, 32, 94, 32, 121, 32, 102, 111, 114, 32, 105, 116, 115, 32, 112, 111, 115, 105, 116, 105, 118, 101, 32, 105, 110, 116, 101, 103, 101, 114, 32, 115, 111, 108, 117, 116, 105, 111, 110, 115, 32, 40, 120, 44, 32, 121, 41, 46, 10};
    print_line(string_zqlndf);
    
    while (1) {
        
        int mode, a, b, c, status;
        
        while (1) {
            // "Enter 1 if you are a human, 2 if you are a Lean4 compiler:"
            int string_ipffbq[59] = {69, 110, 116, 101, 114, 32, 49, 32, 105, 102, 32, 121, 111, 117, 32, 97, 114, 101, 32, 97, 32, 104, 117, 109, 97, 110, 44, 32, 50, 32, 105, 102, 32, 121, 111, 117, 32, 97, 114, 101, 32, 97, 32, 76, 101, 97, 110, 52, 32, 99, 111, 109, 112, 105, 108, 101, 114, 58, 10};
            print_line(string_ipffbq);
            mode = getint();
            if (mode == 1 || mode == 2) {
                break;
            }else{
                // "You are a human or a Lean4 compiler, please try again!"
                int string_fxwbgr[55] = {89, 111, 117, 32, 97, 114, 101, 32, 97, 32, 104, 117, 109, 97, 110, 32, 111, 114, 32, 97, 32, 76, 101, 97, 110, 52, 32, 99, 111, 109, 112, 105, 108, 101, 114, 44, 32, 112, 108, 101, 97, 115, 101, 32, 116, 114, 121, 32, 97, 103, 97, 105, 110, 33, 10};
                print_line(string_fxwbgr);
                continue;
            }
        }
        
        while (1) {
            // "Please input a (a should be a positive integer >= 2):"
            int string_fdyomu[54] = {80, 108, 101, 97, 115, 101, 32, 105, 110, 112, 117, 116, 32, 97, 32, 40, 97, 32, 115, 104, 111, 117, 108, 100, 32, 98, 101, 32, 97, 32, 112, 111, 115, 105, 116, 105, 118, 101, 32, 105, 110, 116, 101, 103, 101, 114, 32, 62, 61, 32, 50, 41, 58, 10};
            print_line(string_fdyomu);
            a = getint();
            if (a >= 2) {
                break;
            }else{
                // "%d isn't a positive integer >= 2, please try again!"
                int string_uecllm[52] = {37, 100, 32, 105, 115, 110, 39, 116, 32, 97, 32, 112, 111, 115, 105, 116, 105, 118, 101, 32, 105, 110, 116, 101, 103, 101, 114, 32, 62, 61, 32, 50, 44, 32, 112, 108, 101, 97, 115, 101, 32, 116, 114, 121, 32, 97, 103, 97, 105, 110, 33, 10};
                print_line_with_d(string_uecllm, a);
                continue;
            }
        }
        
        while (1) {
            // "Please input b (b should be a positive integer):"
            int string_srzcki[49] = {80, 108, 101, 97, 115, 101, 32, 105, 110, 112, 117, 116, 32, 98, 32, 40, 98, 32, 115, 104, 111, 117, 108, 100, 32, 98, 101, 32, 97, 32, 112, 111, 115, 105, 116, 105, 118, 101, 32, 105, 110, 116, 101, 103, 101, 114, 41, 58, 10};
            print_line(string_srzcki);
            b = getint();
            if (b >= 1) {
                break;
            }else{
                // "%d isn't a positive integer, please try again!"
                int string_wgelkh[47] = {37, 100, 32, 105, 115, 110, 39, 116, 32, 97, 32, 112, 111, 115, 105, 116, 105, 118, 101, 32, 105, 110, 116, 101, 103, 101, 114, 44, 32, 112, 108, 101, 97, 115, 101, 32, 116, 114, 121, 32, 97, 103, 97, 105, 110, 33, 10};
                print_line_with_d(string_wgelkh, b);
                continue;
            }
        }
        
        while (1) {
            // "Please input c (c should be a positive integer >= 2):"
            int string_gylwob[54] = {80, 108, 101, 97, 115, 101, 32, 105, 110, 112, 117, 116, 32, 99, 32, 40, 99, 32, 115, 104, 111, 117, 108, 100, 32, 98, 101, 32, 97, 32, 112, 111, 115, 105, 116, 105, 118, 101, 32, 105, 110, 116, 101, 103, 101, 114, 32, 62, 61, 32, 50, 41, 58, 10};
            print_line(string_gylwob);
            c = getint();
            if (c >= 2) {
                break;
            }else{
                // "%d isn't a positive integer >= 2, please try again!"
                int string_zvzywe[52] = {37, 100, 32, 105, 115, 110, 39, 116, 32, 97, 32, 112, 111, 115, 105, 116, 105, 118, 101, 32, 105, 110, 116, 101, 103, 101, 114, 32, 62, 61, 32, 50, 44, 32, 112, 108, 101, 97, 115, 101, 32, 116, 114, 121, 32, 97, 103, 97, 105, 110, 33, 10};
                print_line_with_d(string_zvzywe, c);
                continue;
            }
        }
        
        set_abc_v1(a, b, c);
        if (!assertion) return;
        
        Solve_Diophantine1();
        if(!assertion) return;
        
        if (solver_v1_success) {
            if (mode == 1) {
                print_solution_v1();
            }else{
                generate_Lean4_code_v1();
            }
            if(!assertion) return;
        }else{
            // "-- [Solver V1] solver failed!"
            int string_mfkbjz[30] = {45, 45, 32, 91, 83, 111, 108, 118, 101, 114, 32, 86, 49, 93, 32, 115, 111, 108, 118, 101, 114, 32, 102, 97, 105, 108, 101, 100, 33, 10};
            print_line(string_mfkbjz);
        }
        
        while (1) {
            // "Enter 1 if you want to solve again, 2 if you want to leave:"
            int string_gulkyz[60] = {69, 110, 116, 101, 114, 32, 49, 32, 105, 102, 32, 121, 111, 117, 32, 119, 97, 110, 116, 32, 116, 111, 32, 115, 111, 108, 118, 101, 32, 97, 103, 97, 105, 110, 44, 32, 50, 32, 105, 102, 32, 121, 111, 117, 32, 119, 97, 110, 116, 32, 116, 111, 32, 108, 101, 97, 118, 101, 58, 10};
            print_line(string_gulkyz);
            status = getint();
            if (status == 1 || status == 2) {
                break;
            }else{
                // "You should input 1 or 2, please try again!"
                int string_osehzp[43] = {89, 111, 117, 32, 115, 104, 111, 117, 108, 100, 32, 105, 110, 112, 117, 116, 32, 49, 32, 111, 114, 32, 50, 44, 32, 112, 108, 101, 97, 115, 101, 32, 116, 114, 121, 32, 97, 103, 97, 105, 110, 33, 10};
                print_line(string_osehzp);
                continue;
            }
        }
        
        if(status == 2) {
            break;
        }else{
            continue;
        }
    }
}


void Solve_Diophantine1_research() {
    int exclude_trivial = getint();
    int a_max = getint();
    int a_min = getint();
    int b_max = getint();
    int b_min = getint();
    int c_max = getint();
    int c_min = getint();
    // "exclude_trivial should be 0 or 1!"
    int array_otbpnw[34] = {101, 120, 99, 108, 117, 100, 101, 95, 116, 114, 105, 118, 105, 97, 108, 32, 115, 104, 111, 117, 108, 100, 32, 98, 101, 32, 48, 32, 111, 114, 32, 49, 33, 10};
    assert(exclude_trivial == 0 || exclude_trivial == 1, array_otbpnw);
    if (!assertion) return;
    // "a_max >= a_min >= 2 isn't satisfied!"
    int array_eycepr[37] = {97, 95, 109, 97, 120, 32, 62, 61, 32, 97, 95, 109, 105, 110, 32, 62, 61, 32, 50, 32, 105, 115, 110, 39, 116, 32, 115, 97, 116, 105, 115, 102, 105, 101, 100, 33, 10};
    assert(a_max >= a_min && a_min >= 2, array_eycepr);
    if (!assertion) return;
    // "b_max >= b_min >= 1 isn't satisfied!"
    int array_gdxgpq[37] = {98, 95, 109, 97, 120, 32, 62, 61, 32, 98, 95, 109, 105, 110, 32, 62, 61, 32, 49, 32, 105, 115, 110, 39, 116, 32, 115, 97, 116, 105, 115, 102, 105, 101, 100, 33, 10};
    assert(b_max >= b_min && b_min >= 1, array_gdxgpq);
    if (!assertion) return;
    // "c_max >= c_min >= 2 isn't satisfied!"
    int array_kpnyfs[37] = {99, 95, 109, 97, 120, 32, 62, 61, 32, 99, 95, 109, 105, 110, 32, 62, 61, 32, 50, 32, 105, 115, 110, 39, 116, 32, 115, 97, 116, 105, 115, 102, 105, 101, 100, 33, 10};
    assert(c_max >= c_min && c_min >= 2, array_kpnyfs);
    if (!assertion) return;
    // "-- Generated by Diophantine Solver V1, developed by parkcai, Eureka Lab."
    int string_gkrhit[73] = {45, 45, 32, 71, 101, 110, 101, 114, 97, 116, 101, 100, 32, 98, 121, 32, 68, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 32, 83, 111, 108, 118, 101, 114, 32, 86, 49, 44, 32, 100, 101, 118, 101, 108, 111, 112, 101, 100, 32, 98, 121, 32, 112, 97, 114, 107, 99, 97, 105, 44, 32, 69, 117, 114, 101, 107, 97, 32, 76, 97, 98, 46, 10};
    print_line(string_gkrhit);
    // "-- Consists of transcendental diophantine equations a ^ x + b = c ^ y, for positive integers x, y."
    int string_blzzbf[99] = {45, 45, 32, 67, 111, 110, 115, 105, 115, 116, 115, 32, 111, 102, 32, 116, 114, 97, 110, 115, 99, 101, 110, 100, 101, 110, 116, 97, 108, 32, 100, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 32, 101, 113, 117, 97, 116, 105, 111, 110, 115, 32, 97, 32, 94, 32, 120, 32, 43, 32, 98, 32, 61, 32, 99, 32, 94, 32, 121, 44, 32, 102, 111, 114, 32, 112, 111, 115, 105, 116, 105, 118, 101, 32, 105, 110, 116, 101, 103, 101, 114, 115, 32, 120, 44, 32, 121, 46, 10};
    print_line(string_blzzbf);
    // "-- a, b and c range over the following intervals:"
    int string_gywwje[50] = {45, 45, 32, 97, 44, 32, 98, 32, 97, 110, 100, 32, 99, 32, 114, 97, 110, 103, 101, 32, 111, 118, 101, 114, 32, 116, 104, 101, 32, 102, 111, 108, 108, 111, 119, 105, 110, 103, 32, 105, 110, 116, 101, 114, 118, 97, 108, 115, 58, 10};
    print_line(string_gywwje);
    // "-- %d <= a <= %d"
    int string_vspzra[17] = {45, 45, 32, 37, 100, 32, 60, 61, 32, 97, 32, 60, 61, 32, 37, 100, 10};
    print_line_with_dd(string_vspzra, a_min, a_max);
    // "-- %d <= b <= %d"
    int string_vhrydd[17] = {45, 45, 32, 37, 100, 32, 60, 61, 32, 98, 32, 60, 61, 32, 37, 100, 10};
    print_line_with_dd(string_vhrydd, b_min, b_max);
    // "-- %d <= c <= %d"
    int string_cohpsf[17] = {45, 45, 32, 37, 100, 32, 60, 61, 32, 99, 32, 60, 61, 32, 37, 100, 10};
    print_line_with_dd(string_cohpsf, c_min, c_max);
    if (exclude_trivial) {
        // "-- trivial cases where a, b, c are not pairwise coprime are skipped."
        int string_qgmxvc[69] = {45, 45, 32, 116, 114, 105, 118, 105, 97, 108, 32, 99, 97, 115, 101, 115, 32, 119, 104, 101, 114, 101, 32, 97, 44, 32, 98, 44, 32, 99, 32, 97, 114, 101, 32, 110, 111, 116, 32, 112, 97, 105, 114, 119, 105, 115, 101, 32, 99, 111, 112, 114, 105, 109, 101, 32, 97, 114, 101, 32, 115, 107, 105, 112, 112, 101, 100, 46, 10};
        print_line(string_qgmxvc);
    }else {
        // "-- trivial cases where a, b, c are not pairwise coprime are not skipped."
        int string_lhauqg[73] = {45, 45, 32, 116, 114, 105, 118, 105, 97, 108, 32, 99, 97, 115, 101, 115, 32, 119, 104, 101, 114, 101, 32, 97, 44, 32, 98, 44, 32, 99, 32, 97, 114, 101, 32, 110, 111, 116, 32, 112, 97, 105, 114, 119, 105, 115, 101, 32, 99, 111, 112, 114, 105, 109, 101, 32, 97, 114, 101, 32, 110, 111, 116, 32, 115, 107, 105, 112, 112, 101, 100, 46, 10};
        print_line(string_lhauqg);
    }
    print_line(newline); print_line(newline);
    generate_Claim_Structure();
    print_line(newline); print_line(newline);
    int a = a_min;
    int first_time_protection = 1;
    while (a <= a_max) {
        int b = b_min;
        while (b <= b_max) {
            int c = c_min;
            while (c <= c_max) {
                if (exclude_trivial && (greatest_common_divisor(a, b) >= 2 || greatest_common_divisor(b, c) >= 2 || greatest_common_divisor(a, c) >= 2)) {
                    c = c + 1;
                    continue;
                }
                if (first_time_protection) {
                    first_time_protection = 0;
                }else{
                    print_line(newline);
                }
                Solve_Diophantine1_generate_Lean4_code(a, b, c);
                if (!solver_v1_success) {
                    // "-- panic: solver_v1 has failed."
                    int string_tolabw[32] = {45, 45, 32, 112, 97, 110, 105, 99, 58, 32, 115, 111, 108, 118, 101, 114, 95, 118, 49, 32, 104, 97, 115, 32, 102, 97, 105, 108, 101, 100, 46, 10};
                    print_line(string_tolabw);
                    return;
                }
                c = c + 1;
            }
            b = b + 1;
        }
        a = a + 1;
    }
    print_line(newline);
    // "def main : IO Unit :="
    int string_xovpdd[22] = {100, 101, 102, 32, 109, 97, 105, 110, 32, 58, 32, 73, 79, 32, 85, 110, 105, 116, 32, 58, 61, 10};
    print_line(string_xovpdd);
    // "  IO.println "Native Lean4 check passed.""
    int string_ixuwxf[42] = {32, 32, 73, 79, 46, 112, 114, 105, 110, 116, 108, 110, 32, 34, 78, 97, 116, 105, 118, 101, 32, 76, 101, 97, 110, 52, 32, 99, 104, 101, 99, 107, 32, 112, 97, 115, 115, 101, 100, 46, 34, 10};
    print_line(string_ixuwxf);
}


void Solve_Diophantine1_document() {
    // "-- transcendental_diophantine1.lean"
    int string_gcuwkq[36] = {45, 45, 32, 116, 114, 97, 110, 115, 99, 101, 110, 100, 101, 110, 116, 97, 108, 95, 100, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 49, 46, 108, 101, 97, 110, 10};
    print_line(string_gcuwkq);
    // "-- The 'Type-I transcendental Diophantine equation' refers to equations of the form a ^ x + b = c ^ y in positive integers x and y, where a >= 2, b >= 1, and c >= 2 are fixed integers. While it is difficult to rigorously prove a general algorithm that takes arbitrary (a, b, c) and outputs a complete proof, I propose a heuristic algorithm that is intuitive and extensively validated in finite cases, mainly relying on modular arithmetic and the apparent randomness of primes. Under this approach, such equations fall into two major classes and seven subtypes, with two representative equations provided for each subtype in this file."
    int string_eywzvw[635] = {45, 45, 32, 84, 104, 101, 32, 39, 84, 121, 112, 101, 45, 73, 32, 116, 114, 97, 110, 115, 99, 101, 110, 100, 101, 110, 116, 97, 108, 32, 68, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 32, 101, 113, 117, 97, 116, 105, 111, 110, 39, 32, 114, 101, 102, 101, 114, 115, 32, 116, 111, 32, 101, 113, 117, 97, 116, 105, 111, 110, 115, 32, 111, 102, 32, 116, 104, 101, 32, 102, 111, 114, 109, 32, 97, 32, 94, 32, 120, 32, 43, 32, 98, 32, 61, 32, 99, 32, 94, 32, 121, 32, 105, 110, 32, 112, 111, 115, 105, 116, 105, 118, 101, 32, 105, 110, 116, 101, 103, 101, 114, 115, 32, 120, 32, 97, 110, 100, 32, 121, 44, 32, 119, 104, 101, 114, 101, 32, 97, 32, 62, 61, 32, 50, 44, 32, 98, 32, 62, 61, 32, 49, 44, 32, 97, 110, 100, 32, 99, 32, 62, 61, 32, 50, 32, 97, 114, 101, 32, 102, 105, 120, 101, 100, 32, 105, 110, 116, 101, 103, 101, 114, 115, 46, 32, 87, 104, 105, 108, 101, 32, 105, 116, 32, 105, 115, 32, 100, 105, 102, 102, 105, 99, 117, 108, 116, 32, 116, 111, 32, 114, 105, 103, 111, 114, 111, 117, 115, 108, 121, 32, 112, 114, 111, 118, 101, 32, 97, 32, 103, 101, 110, 101, 114, 97, 108, 32, 97, 108, 103, 111, 114, 105, 116, 104, 109, 32, 116, 104, 97, 116, 32, 116, 97, 107, 101, 115, 32, 97, 114, 98, 105, 116, 114, 97, 114, 121, 32, 40, 97, 44, 32, 98, 44, 32, 99, 41, 32, 97, 110, 100, 32, 111, 117, 116, 112, 117, 116, 115, 32, 97, 32, 99, 111, 109, 112, 108, 101, 116, 101, 32, 112, 114, 111, 111, 102, 44, 32, 73, 32, 112, 114, 111, 112, 111, 115, 101, 32, 97, 32, 104, 101, 117, 114, 105, 115, 116, 105, 99, 32, 97, 108, 103, 111, 114, 105, 116, 104, 109, 32, 116, 104, 97, 116, 32, 105, 115, 32, 105, 110, 116, 117, 105, 116, 105, 118, 101, 32, 97, 110, 100, 32, 101, 120, 116, 101, 110, 115, 105, 118, 101, 108, 121, 32, 118, 97, 108, 105, 100, 97, 116, 101, 100, 32, 105, 110, 32, 102, 105, 110, 105, 116, 101, 32, 99, 97, 115, 101, 115, 44, 32, 109, 97, 105, 110, 108, 121, 32, 114, 101, 108, 121, 105, 110, 103, 32, 111, 110, 32, 109, 111, 100, 117, 108, 97, 114, 32, 97, 114, 105, 116, 104, 109, 101, 116, 105, 99, 32, 97, 110, 100, 32, 116, 104, 101, 32, 97, 112, 112, 97, 114, 101, 110, 116, 32, 114, 97, 110, 100, 111, 109, 110, 101, 115, 115, 32, 111, 102, 32, 112, 114, 105, 109, 101, 115, 46, 32, 85, 110, 100, 101, 114, 32, 116, 104, 105, 115, 32, 97, 112, 112, 114, 111, 97, 99, 104, 44, 32, 115, 117, 99, 104, 32, 101, 113, 117, 97, 116, 105, 111, 110, 115, 32, 102, 97, 108, 108, 32, 105, 110, 116, 111, 32, 116, 119, 111, 32, 109, 97, 106, 111, 114, 32, 99, 108, 97, 115, 115, 101, 115, 32, 97, 110, 100, 32, 115, 101, 118, 101, 110, 32, 115, 117, 98, 116, 121, 112, 101, 115, 44, 32, 119, 105, 116, 104, 32, 116, 119, 111, 32, 114, 101, 112, 114, 101, 115, 101, 110, 116, 97, 116, 105, 118, 101, 32, 101, 113, 117, 97, 116, 105, 111, 110, 115, 32, 112, 114, 111, 118, 105, 100, 101, 100, 32, 102, 111, 114, 32, 101, 97, 99, 104, 32, 115, 117, 98, 116, 121, 112, 101, 32, 105, 110, 32, 116, 104, 105, 115, 32, 102, 105, 108, 101, 46, 10};
    print_line(string_eywzvw);
    // "-- Note that these proofs do not fully rely on traditional Lean methods; instead, Lean serves as a skeleton, while many reusable reasoning primitives are declared using `Claim` and externally verified by the CoLean system in a second-pass revalidation. This is partly due to my limited understanding of Lean and a preference for keeping the document purely ASCII. Nonetheless, I believe the CoLean framework -- using Lean as a scaffold and delegating complex inferences -- has broader relevance for domains less amenable to full formalization, such as physics or philosophy. This file also serves as an early proof-of-concept and testbed for CoLean's development."
    int string_atiyuw[664] = {45, 45, 32, 78, 111, 116, 101, 32, 116, 104, 97, 116, 32, 116, 104, 101, 115, 101, 32, 112, 114, 111, 111, 102, 115, 32, 100, 111, 32, 110, 111, 116, 32, 102, 117, 108, 108, 121, 32, 114, 101, 108, 121, 32, 111, 110, 32, 116, 114, 97, 100, 105, 116, 105, 111, 110, 97, 108, 32, 76, 101, 97, 110, 32, 109, 101, 116, 104, 111, 100, 115, 59, 32, 105, 110, 115, 116, 101, 97, 100, 44, 32, 76, 101, 97, 110, 32, 115, 101, 114, 118, 101, 115, 32, 97, 115, 32, 97, 32, 115, 107, 101, 108, 101, 116, 111, 110, 44, 32, 119, 104, 105, 108, 101, 32, 109, 97, 110, 121, 32, 114, 101, 117, 115, 97, 98, 108, 101, 32, 114, 101, 97, 115, 111, 110, 105, 110, 103, 32, 112, 114, 105, 109, 105, 116, 105, 118, 101, 115, 32, 97, 114, 101, 32, 100, 101, 99, 108, 97, 114, 101, 100, 32, 117, 115, 105, 110, 103, 32, 96, 67, 108, 97, 105, 109, 96, 32, 97, 110, 100, 32, 101, 120, 116, 101, 114, 110, 97, 108, 108, 121, 32, 118, 101, 114, 105, 102, 105, 101, 100, 32, 98, 121, 32, 116, 104, 101, 32, 67, 111, 76, 101, 97, 110, 32, 115, 121, 115, 116, 101, 109, 32, 105, 110, 32, 97, 32, 115, 101, 99, 111, 110, 100, 45, 112, 97, 115, 115, 32, 114, 101, 118, 97, 108, 105, 100, 97, 116, 105, 111, 110, 46, 32, 84, 104, 105, 115, 32, 105, 115, 32, 112, 97, 114, 116, 108, 121, 32, 100, 117, 101, 32, 116, 111, 32, 109, 121, 32, 108, 105, 109, 105, 116, 101, 100, 32, 117, 110, 100, 101, 114, 115, 116, 97, 110, 100, 105, 110, 103, 32, 111, 102, 32, 76, 101, 97, 110, 32, 97, 110, 100, 32, 97, 32, 112, 114, 101, 102, 101, 114, 101, 110, 99, 101, 32, 102, 111, 114, 32, 107, 101, 101, 112, 105, 110, 103, 32, 116, 104, 101, 32, 100, 111, 99, 117, 109, 101, 110, 116, 32, 112, 117, 114, 101, 108, 121, 32, 65, 83, 67, 73, 73, 46, 32, 78, 111, 110, 101, 116, 104, 101, 108, 101, 115, 115, 44, 32, 73, 32, 98, 101, 108, 105, 101, 118, 101, 32, 116, 104, 101, 32, 67, 111, 76, 101, 97, 110, 32, 102, 114, 97, 109, 101, 119, 111, 114, 107, 32, 45, 45, 32, 117, 115, 105, 110, 103, 32, 76, 101, 97, 110, 32, 97, 115, 32, 97, 32, 115, 99, 97, 102, 102, 111, 108, 100, 32, 97, 110, 100, 32, 100, 101, 108, 101, 103, 97, 116, 105, 110, 103, 32, 99, 111, 109, 112, 108, 101, 120, 32, 105, 110, 102, 101, 114, 101, 110, 99, 101, 115, 32, 45, 45, 32, 104, 97, 115, 32, 98, 114, 111, 97, 100, 101, 114, 32, 114, 101, 108, 101, 118, 97, 110, 99, 101, 32, 102, 111, 114, 32, 100, 111, 109, 97, 105, 110, 115, 32, 108, 101, 115, 115, 32, 97, 109, 101, 110, 97, 98, 108, 101, 32, 116, 111, 32, 102, 117, 108, 108, 32, 102, 111, 114, 109, 97, 108, 105, 122, 97, 116, 105, 111, 110, 44, 32, 115, 117, 99, 104, 32, 97, 115, 32, 112, 104, 121, 115, 105, 99, 115, 32, 111, 114, 32, 112, 104, 105, 108, 111, 115, 111, 112, 104, 121, 46, 32, 84, 104, 105, 115, 32, 102, 105, 108, 101, 32, 97, 108, 115, 111, 32, 115, 101, 114, 118, 101, 115, 32, 97, 115, 32, 97, 110, 32, 101, 97, 114, 108, 121, 32, 112, 114, 111, 111, 102, 45, 111, 102, 45, 99, 111, 110, 99, 101, 112, 116, 32, 97, 110, 100, 32, 116, 101, 115, 116, 98, 101, 100, 32, 102, 111, 114, 32, 67, 111, 76, 101, 97, 110, 39, 115, 32, 100, 101, 118, 101, 108, 111, 112, 109, 101, 110, 116, 46, 10};
    print_line(string_atiyuw);
    // "-- Eureka Lab, parkcai, 25/08/01."
    int string_vgucww[34] = {45, 45, 32, 69, 117, 114, 101, 107, 97, 32, 76, 97, 98, 44, 32, 112, 97, 114, 107, 99, 97, 105, 44, 32, 50, 53, 47, 48, 56, 47, 48, 49, 46, 10};
    print_line(string_vgucww);
    print_line(newline); print_line(newline); print_line(newline);
    generate_Claim_Structure();
    print_line(newline); print_line(newline); print_line(newline);
    Solve_Diophantine1_generate_Lean4_code(2, 6, 9);
    print_line(newline);
    Solve_Diophantine1_generate_Lean4_code(3, 6, 8);
    print_line(newline); print_line(newline); print_line(newline); 
    Solve_Diophantine1_generate_Lean4_code(2, 4, 7);
    print_line(newline);
    Solve_Diophantine1_generate_Lean4_code(3, 6, 11);
    print_line(newline); print_line(newline); print_line(newline); 
    Solve_Diophantine1_generate_Lean4_code(2, 4, 6);
    print_line(newline);
    Solve_Diophantine1_generate_Lean4_code(3, 1, 9);
    print_line(newline); print_line(newline); print_line(newline); 
    Solve_Diophantine1_generate_Lean4_code(7, 3, 10);
    print_line(newline);
    Solve_Diophantine1_generate_Lean4_code(17, 3, 20);
    print_line(newline); print_line(newline); print_line(newline); 
    Solve_Diophantine1_generate_Lean4_code(2, 1, 3);
    print_line(newline);
    Solve_Diophantine1_generate_Lean4_code(2, 89, 91);
    print_line(newline); print_line(newline); print_line(newline); 
    Solve_Diophantine1_generate_Lean4_code(2, 5, 11);
    print_line(newline);
    Solve_Diophantine1_generate_Lean4_code(3, 5, 7);
    print_line(newline); print_line(newline); print_line(newline); 
    Solve_Diophantine1_generate_Lean4_code(3, 7, 2);
    print_line(newline);
    Solve_Diophantine1_generate_Lean4_code(3, 10, 13);
    print_line(newline); print_line(newline); print_line(newline);
    // "def main : IO Unit :="
    int string_fvlhuf[22] = {100, 101, 102, 32, 109, 97, 105, 110, 32, 58, 32, 73, 79, 32, 85, 110, 105, 116, 32, 58, 61, 10};
    print_line(string_fvlhuf);
    // "  IO.println "Native Lean4 check passed.""
    int string_afiwzh[42] = {32, 32, 73, 79, 46, 112, 114, 105, 110, 116, 108, 110, 32, 34, 78, 97, 116, 105, 118, 101, 32, 76, 101, 97, 110, 52, 32, 99, 104, 101, 99, 107, 32, 112, 97, 115, 115, 101, 100, 46, 34, 10};
    print_line(string_afiwzh);
}

// ------------------------------ program entrance ------------------------------

int main() {
    while (1) {
        int usage = getint();
        if (usage == 0) {
            Solve_Diophantine1_info();
        }else if (usage == 1) {
            Solve_Diophantine1_shell();
        }else if (usage == 2) {
            Solve_Diophantine1_research();
        }else if (usage == 3) {
            Solve_Diophantine1_document();
        }else if (usage == -1) {
            Solve_Diophantine1_backdoor();
            continue;
        }else{
            // "Unknown usage %d, try ./diophantine 0/1/2/3!"
            int string_cxxzoe[45] = {85, 110, 107, 110, 111, 119, 110, 32, 117, 115, 97, 103, 101, 32, 37, 100, 44, 32, 116, 114, 121, 32, 46, 47, 100, 105, 111, 112, 104, 97, 110, 116, 105, 110, 101, 32, 48, 47, 49, 47, 50, 47, 51, 33, 10};
            print_line_with_d(string_cxxzoe, usage);
        }
        return 0;
    }
}

