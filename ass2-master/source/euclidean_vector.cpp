// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "comp6771/euclidean_vector.hpp"
#include <iostream>

namespace comp6771 {
	// Implement solution here
	auto operator==(euclidean_vector const& a, euclidean_vector const& b) -> bool {
		if (a.dimensions() != b.dimensions())
			return false;
		for (int i = 0; i < a.dimensions(); ++i)
			if (a.a[i] != b.a[i])
				return false;
		return true;
	}
	auto operator!=(euclidean_vector const& a, euclidean_vector const& b) -> bool {
		return !(a == b);
	}
	auto operator+(euclidean_vector const& a, euclidean_vector const& b) -> euclidean_vector {
		euclidean_vector ans;
		if (a.dimensions() != b.dimensions())
			throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(a.dimensions())
			                             + ") and RHS(" + std::to_string(b.dimensions())
			                             + ") do not match");
		else {
			ans.n = a.dimensions();
			for (int i = 0; i < a.dimensions(); ++i)
				ans.a[i] = a.a[i] + b.a[i];
		}
		return ans;
	}

	auto operator-(euclidean_vector const& a, euclidean_vector const& b) -> euclidean_vector {
		euclidean_vector ans;
		if (a.dimensions() != b.dimensions())
			throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(a.dimensions())
			                             + ") and RHS(" + std::to_string(b.dimensions())
			                             + ") do not match");
		else {
			ans.n = a.dimensions();
			for (int i = 0; i < a.dimensions(); ++i)
				ans.a[i] = a.a[i] - b.a[i];
		}
		return ans;
	}

	auto operator*(euclidean_vector const& a, double b) -> euclidean_vector {
		euclidean_vector ans;
		ans.n = a.dimensions();
		for (int i = 0; i < a.dimensions(); ++i)
			ans.a[i] = a.a[i] * b;
		return ans;
	}

	auto operator/(euclidean_vector const& a, double b) -> euclidean_vector {
		if (b == 0.0)
			throw euclidean_vector_error("Invalid vector division by 0");
		euclidean_vector ans;
		ans.n = a.dimensions();
		for (int i = 0; i < a.dimensions(); ++i)
			ans.a[i] = a.a[i] / b;
		return ans;
	}

	auto operator<<(std::ostream& a, euclidean_vector const& b) -> std::ostream& {
		a << "[";
		for (int i = 0; i < b.dimensions(); ++i) {
			a << b.a[i];
			if (i != b.dimensions() - 1)
				a << ' ';
		}
		return a << ']';
	}

	auto euclidean_norm(euclidean_vector const& v) -> double {
		if (v.dimensions() == 0)
			throw euclidean_vector_error("euclidean_vector with no \
			dimensions does not have a unit vector");
		double ans = 0;
		for (int i = 0; i < v.dimensions(); ++i)
			ans += v.a[i] * v.a[i];
		return sqrt(ans);
	}

	auto unit(euclidean_vector const& v) -> euclidean_vector {
		if (v.dimensions() == 0)
			throw euclidean_vector_error("euclidean_vector with no dimensions does \
			not have a unit vector");
		if (euclidean_norm(v) == 0)
			throw euclidean_vector_error("euclidean_vector with zero euclidean \
			normal does not have a unit vector");
		return v / euclidean_norm(v);
	}

	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double {
		if (x.dimensions() != y.dimensions())
			throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(x.dimensions())
			                             + ") and RHS(" + std::to_string(y.dimensions())
			                             + ") do not match");
		double ans = 0.0;
		for (int i = 0; i < x.dimensions(); ++i)
			ans += x.a[i] * y.a[i];
		return ans;
	}
} // namespace comp6771