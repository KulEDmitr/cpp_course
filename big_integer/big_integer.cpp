#include "big_integer.h"
#include <iostream>
#include <algorithm>

big_integer::big_integer() {
    vec.assign(2, 0);
}

big_integer::big_integer(int a) {
    vec.push_back(static_cast<uint32_t>(a));
    vec.push_back((a < 0) ? UINT32_MAX : 0);
}

big_integer::big_integer(std::string const &str) {
    *this = 0;
    size_t i = 0;
    bool sign = false;
    if (str[i] - '0' < 0) {
        sign = !(str[i++] - '-');
    }
    uint32_t block = 0;
    int pow = 1;
    for (; i < str.length(); ++i) {
        block *= 10;
        block += str[i] - '0';
        pow *= 10;
        if (pow == MAX || i == str.length() - 1) {
            *this *= pow;
            *this += block;
            pow = 1;
            block = 0;
        }
    }
    vec.push_back(0);
    if (sign) {
        *this = -(*this);
    }
    del_rep_sign();
}

big_integer &big_integer::operator+=(big_integer const &rhs) {
    uint32_t sign = vec.back();
    while (vec.size() < rhs.vec.size()) {
        vec.push_back(sign);
    }
    uint32_t sum, carry = 0;
    for (size_t i = 0; i < rhs.vec.size(); ++i) {
        sum = vec[i] + rhs.vec[i] + carry;
        carry = ((sum < rhs.vec[i]) || (sum < vec[i])) ? 1 : 0;
        vec[i] = sum;
    }
    if (rhs.vec.back() == UINT32_MAX) {
        carry = 0;
    }
    for (size_t i = rhs.vec.size(); i < vec.size(); ++i) {
        sum = vec[i] + carry;
        carry = (sum < vec[i]) ? 1 : 0;
        vec[i] = sum;
        if (!carry) {
            break;
        }
    }
    if (vec.back() != 0 && vec.back() != UINT32_MAX) {
        vec.push_back(sign);
    }
    del_rep_sign();
    return *this;
}

big_integer &big_integer::operator-=(big_integer const &rhs) {
    return *this += -rhs;
}

big_integer big_integer::operator+() const {
    return *this;
}

big_integer big_integer::operator-() const {
    return ++(~(*this));
}

big_integer big_integer::operator~() const {
    big_integer inv(*this);
    for (size_t i = 0; i < inv.vec.size(); ++i) {
        inv.vec[i] = ~inv.vec[i];
    }
    inv.del_rep_sign();
    return inv;
}

big_integer &big_integer::operator++() {
    return *this += 1;
}

big_integer big_integer::operator++(int) {
    big_integer post(*this);
    ++(*this);
    return post;
}

big_integer &big_integer::operator--() {
    return *this -= 1;
}

big_integer big_integer::operator--(int) {
    big_integer post(*this);
    --(*this);
    return post;
}

bool operator==(big_integer const &a, big_integer const &b) {
    return a.vec == b.vec;
}

bool operator!=(big_integer const &a, big_integer const &b) {
    return !(a.vec == b.vec);
}

bool operator<(big_integer const &a, big_integer const &b) {
    return ((a - b).vec.back() == UINT32_MAX);
}

bool operator>(big_integer const &a, big_integer const &b) {
    return b < a;
}

bool operator>=(big_integer const &a, big_integer const &b) {
    return !(a < b);
}

bool operator<=(big_integer const &a, big_integer const &b) {
    return !(b < a);
}

big_integer &big_integer::operator*=(big_integer const &rhs) {
    if (*this == 0 || rhs == 0) {
        return *this = 0;
    }
    bool sign = (vec.back() != rhs.vec.back());
    if (vec.back()) {
        *this = -(*this);
    }
    big_integer hlp = (rhs.vec.back()) ? -rhs : rhs;
    my_vector<uint32_t> ans;
    ans.assign(vec.size() + hlp.vec.size(), 0);
    for (size_t i = 0; i < vec.size(); ++i) {
        uint32_t carry = 0;
        for (size_t j = 0; j < rhs.vec.size(); ++j) {
            uint64_t tmp = static_cast<uint64_t>(vec[i]) * static_cast<uint64_t>(hlp.vec[j])
                           + static_cast<uint64_t>(ans[i + j]) + static_cast<uint64_t>(carry);
            ans[i + j] = tmp;
            carry = tmp >> BASE;
        }
        ans[i + rhs.vec.size()] += carry;
    }
    vec = ans;
    if (sign) {
        *this = -*this;
    }
    del_rep_sign();
    return *this;
}

std::pair<big_integer, uint32_t> div_by_short(big_integer const &a, uint32_t const &b) {
    big_integer ans(a);
    uint64_t cur, carry = 0;
    for (size_t i = ans.vec.size(); i > 0; --i) {
        cur = (carry << BASE) + ans.vec[i - 1];
        ans.vec[i - 1] = cur / b;
        carry = cur % b;
    }
    ans.del_rep_sign();
    return {ans, carry};
}

std::pair<big_integer, big_integer> div_by_short_b_i(big_integer const &a, big_integer const &b) {
    if (b == 1 || b == -1) {
        return {(a * b), 0};
    }
    bool sign = (a.vec.back() != b.vec.back());
    big_integer a1(a), a2(b);
    if (a.vec.back()) {
        a1 = -a1;
    }
    if (b.vec.back()) {
        a2 = -a2;
    }
    if (a1 < a2) {
        return {0, a};
    }
    big_integer rem, ans;
    std::pair<big_integer, uint32_t> fuf = div_by_short(a1, a2.vec[0]);
    ans = fuf.first;
    rem.vec[0] = fuf.second;
    if (sign) {
        ans = -ans;
    }
    if (a.vec.back() == UINT32_MAX) {
        rem = -rem;
    }
    ans.del_rep_sign();
    rem.del_rep_sign();
    return {ans, rem};
}

std::pair<big_integer, big_integer> div_mod(big_integer const &a, big_integer const &b) {
    if (a == 0) {
        return {0, 0};
    }
    if (b.vec.size() == 2) {
        return div_by_short_b_i(a, b);
    }
    bool sign = (a.vec.back() != b.vec.back());
    big_integer a1(a), a2(b);
    if (a.vec.back()) {
        a1 = -a1;
    }
    if (b.vec.back()) {
        a2 = -a2;
    }
    if (a1 < a2) {
        return {0, a};
    }

    big_integer tmp(0), t_n(0);
    big_integer rem, cur;
    uint32_t norm = (static_cast<uint64_t>(1) << BASE)
            / static_cast<uint64_t >((a2.vec[a2.vec.size() - 2] + 1));
    t_n.vec[0] = norm;
    a1 *= t_n;
    a2 *= t_n;
    uint32_t b_ = a2.vec[a2.vec.size() - 2];
    uint64_t a__;
    size_t a_size = a1.vec.size(), b_size = a2.vec.size();
    my_vector<uint32_t> ans;
    ans.assign(a_size - b_size + 1, 0);
    size_t pos = a_size - b_size;
    my_vector<uint32_t> u64;
    if (pos == 0) {
        a__ = a1.vec[a_size - 2] / b_;
        tmp.vec[0] = static_cast<uint32_t>(a__);
        cur = a2 * tmp;
        while (cur > a1) {
            cur -= a2;
            --tmp;
        }
        rem = a1 - cur;
        a1 = tmp;
    } else {
        rem.vec.pop_back();
        rem.vec.pop_back();
        for (size_t i = a_size - b_size - 1, j = b_size; j > 0; --j) {
            rem.vec.push_back(a1.vec[++i]);
        }
        while (pos > 0) {
            rem <<= BASE;
            rem.vec[0] = a1.vec[pos - 1];
            a__ = rem.vec[rem.vec.size() - 2];
            if (rem.vec.size() > b_size) {
                a__ <<= BASE;
                a__ += rem.vec[rem.vec.size() - 3];
            }
            a__ /= b_;
            uint32_t carry = a__ >> BASE;
            ans[pos] += carry;
            uint32_t res = a__;
            if (carry) {
                u64.assign(3, 0);
                u64[0] = res;
                u64[1] = carry;
            } else {
                u64.assign(2, 0);
                u64[0] = res;
            }
            tmp.vec = u64;
            cur = a2 * tmp;
            while (cur > rem) {
                --res;
                cur -= a2;
            }
            ans[--pos] = res;
            rem -= cur;
        }
        ans.push_back(0);
        a1.vec = ans;
    }
    if (sign) {
        a1 = -a1;
    }
    rem /= t_n;
    if (a.vec.back() == UINT32_MAX) {
        rem = -rem;
    }
    a1.del_rep_sign();
    rem.del_rep_sign();
    return {a1, rem};
}

big_integer &big_integer::operator/=(big_integer const &rhs) {
    return *this = div_mod(*this, rhs).first;
}

big_integer &big_integer::operator%=(big_integer const &rhs) {
    return *this = div_mod(*this, rhs).second;
}

big_integer &big_integer::bit_operation(big_integer const &rhs,
                                        const std::function<uint32_t(uint32_t, uint32_t)> function) {
    uint32_t sign = vec.back();
    while (vec.size() < rhs.vec.size()) {
        vec.push_back(sign);
    }
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] = function(vec[i], (i < rhs.vec.size()) ? rhs.vec[i] : rhs.vec.back());
    }
    del_rep_sign();
    return *this;
}

big_integer &big_integer::operator&=(const big_integer &rhs) {
    return bit_operation(rhs, [](uint32_t a, uint32_t b) { return a & b; });
}

big_integer &big_integer::operator|=(const big_integer &rhs) {
    return bit_operation(rhs, [](uint32_t a, uint32_t b) { return a | b; });
}

big_integer &big_integer::operator^=(big_integer const &rhs) {
    return bit_operation(rhs, [](uint32_t a, uint32_t b) { return a ^ b; });
}

big_integer &big_integer::operator<<=(int rhs) {
    if (rhs < 0) {
        return *this >>= -rhs;
    }
    if (rhs == 0) {
        return *this;
    }
    int rem = rhs % 32;
    size_t size = vec.size();
    int count = ((rem) ? rhs / BASE + 1 : rhs / BASE);
    while (vec.size() - count < 0) {
        vec.push_back(0);
    }
    for (size_t i = (vec.size() - size); i < count; ++i) {
        vec.push_back(vec[vec.size() - count]);
    }
    int j = size - 1;
    while (j - count >= 0) {
        vec[j] = vec[j - count];
        --j;
    }
    for (size_t i = 0; i <= j; ++i) {
        vec[i] = 0;
    }
    if (rem) {
        *this >>= (BASE - rem);
    } else {
        del_rep_sign();
    }
    return *this;
}

big_integer &big_integer::operator>>=(int rhs) {
    if (rhs < 0) {
        return *this <<= -rhs;
    }
    if (rhs == 0) {
        del_rep_sign();
        return *this;
    }
    int count = rhs / 32;
    int rem = rhs % 32;
    uint32_t sign = vec.back();
    for (int i = 0; i < count; ++i) {
        vec.pop_back();
    }
    uint32_t tmp;
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        tmp = (vec[i + 1] % (1 << rem)) << BASE - rem;
        vec[i] = (vec[i] >> rem) + tmp;
    }
    vec.push_back(sign);
    del_rep_sign();
    return *this;
}

big_integer operator+(big_integer a, big_integer const &b) {
    return a += b;
}

big_integer operator-(big_integer a, big_integer const &b) {
    return a -= b;
}

big_integer operator*(big_integer a, big_integer const &b) {
    return a *= b;
}

big_integer operator/(big_integer a, big_integer const &b) {
    return a /= b;
}

big_integer operator%(big_integer a, big_integer const &b) {
    return a %= b;
}

big_integer operator&(big_integer a, big_integer const &b) {
    return a &= b;
}

big_integer operator|(big_integer a, big_integer const &b) {
    return a |= b;
}

big_integer operator^(big_integer a, big_integer const &b) {
    return a ^= b;
}

big_integer operator<<(big_integer a, int b) {
    return a <<= b;
}

big_integer operator>>(big_integer a, int b) {
    return a >>= b;
}

void big_integer::del_rep_sign() {
    uint32_t sign = vec.back();
    while (vec.size() > 1 && vec.back() == sign) {
        vec.pop_back();
    }
    if (vec.back() == 0 && sign == UINT32_MAX) {
        vec.push_back(sign);
    }
    vec.push_back(sign);
}

std::string to_string(big_integer const &a) {
    std::string res;
    big_integer b = a;
    if (b.vec.back()) {
        b = -b;
        res += '-';
    }
    my_vector<uint32_t> blocks(b.vec.size());
    size_t len = 0;
    while (b > 0) {
        std::pair<big_integer, uint32_t> block = div_by_short(b, MAX);
        blocks[len++] = block.second;
        b = block.first;
    }
    for (size_t i = len; i > 0; --i) {
        std::string digit = std::to_string(blocks[i - 1]);
        if (i != len) {
            res += std::string(9 - digit.length(), '0');
        }
        res += digit;
    }
    if (res.empty()) {
        res = "0";
    }
    return res;
}

std::istream &operator>>(std::istream &s, big_integer &a) {
    std::string input;
    s >> input;
    a = *new big_integer(input);
    return s;
}

std::ostream &operator<<(std::ostream &s, big_integer const &a) {
    return s << to_string(a);
}