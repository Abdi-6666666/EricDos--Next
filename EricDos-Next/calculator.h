#pragma once
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "bitcpp.h"
#include <cctype>

// 说明：支持读取整行算式并计算，支持小数、加减乘除、括号和一元+/-。
// 示例输入：13*(2+123/2)-4  （也支持中文全角括号：13*（2+123/2）-4）

namespace {
    const std::string* g_expr = nullptr;
    size_t g_pos = 0;

    void skipSpaces() {
        while (g_pos < g_expr->size() && std::isspace(static_cast<unsigned char>((*g_expr)[g_pos]))) ++g_pos;
    }

    double parseExpression(); // 前向声明

    double parseNumber() {
        skipSpaces();
        size_t start = g_pos;
        // 允许前导正负号作为数字的一部分（也由一元操作处理，但这里也支持）
        if (g_pos < g_expr->size() && ((*g_expr)[g_pos] == '+' || (*g_expr)[g_pos] == '-')) ++g_pos;
        bool hasDigits = false;
        while (g_pos < g_expr->size() && (std::isdigit(static_cast<unsigned char>((*g_expr)[g_pos])) || (*g_expr)[g_pos] == '.')) {
            hasDigits = true;
            ++g_pos;
        }
        if (g_pos < g_expr->size() && ((*g_expr)[g_pos] == 'e' || (*g_expr)[g_pos] == 'E')) {
            ++g_pos;
            if (g_pos < g_expr->size() && ((*g_expr)[g_pos] == '+' || (*g_expr)[g_pos] == '-')) ++g_pos;
            bool expDigits = false;
            while (g_pos < g_expr->size() && std::isdigit(static_cast<unsigned char>((*g_expr)[g_pos]))) {
                expDigits = true;
                ++g_pos;
            }
            if (!expDigits) throw std::runtime_error("非法的科学计数法");
        }
        if (!hasDigits) throw std::runtime_error("期望数字");
        double val = 0.0;
        try {
            val = std::stod(g_expr->substr(start, g_pos - start));
        }
        catch (...) {
            throw std::runtime_error("无法解析数字");
        }
        skipSpaces();
        return val;
    }

    double parseFactor() {
        skipSpaces();
        if (g_pos >= g_expr->size()) throw std::runtime_error("意外末尾");
        char c = (*g_expr)[g_pos];
        if (c == '(') {
            ++g_pos;
            double val = parseExpression();
            skipSpaces();
            if (g_pos >= g_expr->size() || (*g_expr)[g_pos] != ')') throw std::runtime_error("缺少右括号");
            ++g_pos;
            skipSpaces();
            return val;
        }
        // 一元 + / -
        if (c == '+' || c == '-') {
            ++g_pos;
            double v = parseFactor();
            return (c == '-') ? -v : v;
        }
        // 否则数字
        return parseNumber();
    }

    double parseTerm() {
        double val = parseFactor();
        while (true) {
            skipSpaces();
            if (g_pos >= g_expr->size()) break;
            char op = (*g_expr)[g_pos];
            if (op != '*' && op != '/') break;
            ++g_pos;
            double rhs = parseFactor();
            if (op == '*') val *= rhs;
            else {
                if (rhs == 0.0) throw std::runtime_error("除以零错误");
                val /= rhs;
            }
        }
        return val;
    }

    double parseExpression() {
        double val = parseTerm();
        while (true) {
            skipSpaces();
            if (g_pos >= g_expr->size()) break;
            char op = (*g_expr)[g_pos];
            if (op != '+' && op != '-') break;
            ++g_pos;
            double rhs = parseTerm();
            if (op == '+') val += rhs;
            else val -= rhs;
        }
        return val;
    }
}

void calculator() {
    clear_screen();
    std::cout << "---Calculator ---" << std::endl;
    std::cout << "Enter expression: ";
    std::string line;
    if (!std::getline(std::cin, line)) return;

    // 兼容中文全角括号
    for (char& ch : line) {
        if (ch == (char)0xEF) { /* noop for safety, keep simple replacement below */ }
    }
    // 简单替换全角括号（也处理常见中文输入习惯）
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == '\uFF08') line[i] = '('; // 全角左括号
        else if (line[i] == '\uFF09') line[i] = ')'; // 全角右括号
    }

    try {
        g_expr = &line;
        g_pos = 0;
        double result = parseExpression();
        skipSpaces();
        if (g_pos != g_expr->size()) {
            throw std::runtime_error("在位置 " + std::to_string(g_pos) + " 发现多余字符");
        }
        std::cout << "Result: " << result << std::endl;
    }
    catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    // 清理全局指针以防误用
    g_expr = nullptr;
    g_pos = 0;
}

#endif