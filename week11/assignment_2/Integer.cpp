
//
// Created by 김혁진 on 2019/11/11.
//

#include "Integer.h"
#include "Float.h"
#include "Complex.h"

int Integer::parse_string(const std::string& str) {
    /**
     * 문자열을 int로 변환하는 함수
     */
    int result = atoi(str.c_str());
    return result;
}
 
Integer::Integer() {
    /**
     * value를 0으로 저장
     */
	this->value = 0;
}

Integer::Integer(int _value) {
    /**
     * 입력받은 int 값(_value)을 value에 저장
     */
	this->value = _value;
}

Integer::Integer(const std::string& str) {
    /**
     * Integer의 parse_string 함수를 통해 입력받은 문자열 값을 int 값으로 value에 저장
     */
	int newvalue = parse_string(str);
	this->value = newvalue;
}

Number *Integer::add(Number * num) {
    /**
     * this->value + num->value // num의 value는 private 이므로 호출 불가능 (단순 개념 설명임)
     * this의 값과 parameter로 들어온 num의 value를 더하는 함수
     *
     * 아래의 사항은 add, sub, mul, div 모두 해당됨
     *
     * this와 num 중 더 수의 범위가 큰 타입으로 return 한다.
     * 계산에 사용된 값은 delete한다.
     *
     * 수의 범위
     * INTEGER -> FLOAT -> COMPLEX
     *
     * Integer 값이 들어온 경우 입력으로 들어온 num 값을 Integer 타입으로 캐스팅 후 값 사용
     * Integer 는 값을 return 하기 전 this를 delete 하거나 num을 delete
     * (새로운 객체를 생성해 return 할 경우 this와 Integer로 캐스팅한 num 값을 모두 delete)
     * (this나 캐스팅한 num을 return 할 경우 return 하지 않는 값을 delete)
     *
     * Float 값이 들어온 경우 입력으로 들어온 num 값을 Float 타입으로 캐스팅 후 값 사용
     * Complex 값이 들어온 경우 입력으로 들어온 num 값을 Complex 타입으로 캐스팅 후 값 사용
     * Float와 Complex는 값을 return 하기 전 this를 delete 함 (새로운 객체를 생성해 return 하거나 parameter 의 값을 set_val 후 return)
     *
     * 타입 검사는 num->types()를 이용 (if check, else if check)
     * enum 값이 어떠한 type에도 속하지 않으면 nullptr 반환
     *
     * enum 값은 INTEGER, FLOAT, COMPLEX 과 같이 접근 가능
     */
    if (num->types() == INTEGER) {
		Integer* a = dynamic_cast<Integer*>(num);
		a->set_val(a->val() + this->value);
		delete(this);
		return a;
    } else if (num->types() == FLOAT) {
		Float* a = dynamic_cast<Float*>(num);
		a->set_val(a->val() + this->value);
		delete(this);
		return a;
    } else if (num->types() == COMPLEX) {
		Complex* a = dynamic_cast<Complex*>(num);
		a->set_val(a->real() + this->value, a->imag());
		delete(this);
		return a;
    } else {
		return nullptr;
    }

    return nullptr;
}

Number *Integer::sub(Number * num) {
    /**
     * this->value - num->value // num의 value는 private 이므로 호출 불가능 (단순 개념 설명임)
     * this의 값과 parameter로 들어온 num의 value를 빼는 함수
     */

	if (num->types() == INTEGER) {
		Integer* a = dynamic_cast<Integer*>(num);
		a->set_val(this->value - a->val());
		delete(this);
		return a;
	}
	else if (num->types() == FLOAT) {
		Float* a = dynamic_cast<Float*>(num);
		a->set_val(this->value - a->val());
		delete(this);
		return a;
	}
	else if (num->types() == COMPLEX) {
		Complex* a = dynamic_cast<Complex*>(num);
		a->set_val(this->value - a->real(), a->imag());
		delete(this);
		return a;
	}
	else {
		return nullptr;
	}

	return nullptr;
}

Number *Integer::mul(Number * num) {
    /**
     * this->value * num->value // num의 value는 private 이므로 호출 불가능 (단순 개념 설명임)
     * this의 값과 parameter로 들어온 num의 value를 곱하는 함수
     *
     * Complex 값은 실수부와 허수부 모두에 this->value값을 곱해줘야 함
     */
	if (num->types() == INTEGER) {
		Integer* a = dynamic_cast<Integer*>(num);
		a->set_val(a->val() * this->value);
		delete(this);
		return a;
	}
	else if (num->types() == FLOAT) {
		Float* a = dynamic_cast<Float*>(num);
		a->set_val(a->val() * this->value);
		delete(this);
		return a;
	}
	else if (num->types() == COMPLEX) {
		Complex* a = dynamic_cast<Complex*>(num);
		a->set_val(a->real() * this->value, a->imag() * this->value);
		delete(this);
		return a;
	}
	else {
		return nullptr;
	}

	return nullptr;
}

Number *Integer::div(Number * num) {
    /**
     * this->value / num->value // num의 value는 private 이므로 호출 불가능 (단순 개념 설명임)
     * this의 값과 parameter로 들어온 num의 value를 더하는 함수
     *
     * Type이 COMPLEX 경우 nullptr 를 반환한다.
     * 이 때는 this와 num 모두 delete하지 않는다.
     */
	if (num->types() == INTEGER) {
		Integer* a = dynamic_cast<Integer*>(num);
		if (a->val() == 0) {
			return nullptr;
		}
		else {
			a->set_val(this->value / a->val());
			delete(this);
			return a;
		}
	}
	else if (num->types() == FLOAT) {
		Float* a = dynamic_cast<Float*>(num);
		if (a->val() == 0) {
			return nullptr;
		}
		else {
			a->set_val(this->value / a->val());
			delete(this);
		}
		return a;
	}
	else if (num->types() == COMPLEX) {
		return nullptr;
	}
	else {
		return nullptr;
	}

    return nullptr;
}

void Integer::set_val(int val) {
	this->value = val;
}

int Integer::val() const {
    /**
     * value 값을 return하는 함수 (value의 getter)
     */

    return this->value; // 구현한거 아님;;
}

Number::type Integer::types() const {
    /**
     * Number의 enum 값인 INTEGER 값을 반환
     */

    return this->INTEGER; // 구현한거 아님;;
}

std::string Integer::to_string() const {
    /**
     * int 값의 string
     */
    return std::to_string(value);
}

