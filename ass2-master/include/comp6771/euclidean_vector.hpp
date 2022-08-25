#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <iostream>
#include <list>
#include <math.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what)
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		euclidean_vector() {
			n = 0;
		}
		euclidean_vector(int num, double v) {
			n = num;
			for (int i = 0; i < n; ++i)
				a[i] = v;
		}
		explicit euclidean_vector(int num) {
			n = num;
			for (int i = 0; i < n; ++i)
				a[i] = 0;
		}
		euclidean_vector(std::vector<double>::const_iterator s, std::vector<double>::const_iterator t) {
			n = 0;
			for (auto it = s; it != t; ++it) {
				a[n++] = *it;
			}
		}
		euclidean_vector(std::initializer_list<double> v) {
			n = 0;
			for (auto it = v.begin(); it != v.end(); ++it)
				a[n++] = *it;
		}
		euclidean_vector(const euclidean_vector& x) {
			n = x.n;
			for (int i = 0; i < n; ++i)
				a[i] = x.a[i];
		}
		euclidean_vector(euclidean_vector&& x) {
			n = x.n;
			for (int i = 0; i < n; ++i)
				a[i] = x.a[i];
		}
		~euclidean_vector() {}

		euclidean_vector& operator=(const euclidean_vector& x) {
			n = x.n;
			for (int i = 0; i < n; ++i)
				a[i] = x.a[i];
			return *this;
		}
		euclidean_vector& operator=(euclidean_vector&& x) {
			n = x.n;
			for (int i = 0; i < n; ++i)
				a[i] = x.a[i];
			return *this;
		}
		double operator[](int const x) const {
			return a[x];
		}
		double operator[](int const x) {
			return a[x];
		}
		euclidean_vector operator+() {
			return *this;
		}
		euclidean_vector operator-() {
			euclidean_vector ans = *this;
			for (int i = 0; i < ans.n; ++i)
				ans.a[i] = -a[i];
			return ans;
		}
		euclidean_vector& operator+=(euclidean_vector const& x) {
			if (n != x.n)
				throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(n) + ") and RHS("
				                             + std::to_string(x.n) + ") do not match");
			else {
				for (int i = 0; i < n; ++i)
					a[i] += x.a[i];
			}
			return *this;
		}
		euclidean_vector& operator-=(euclidean_vector const& x) {
			if (n != x.n)
				throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(n) + ") and RHS("
				                             + std::to_string(x.n) + ") do not match");
			else {
				for (int i = 0; i < n; ++i)
					a[i] -= x.a[i];
			}
			return *this;
		}
		euclidean_vector& operator*=(double x) {
			for (int i = 0; i < n; ++i)
				a[i] *= x;
			return *this;
		}
		euclidean_vector& operator/=(double x) {
			if (x == 0.0)
				throw euclidean_vector_error("Invalid vector division by 0");
			else {
				for (int i = 0; i < n; ++i)
					a[i] /= x;
			}
			return *this;
		}
		explicit operator std::vector<double>() const {
			std::vector<double> ans;
			for (int i = 0; i < n; ++i)
				ans.push_back(a[i]);
			return ans;
		}
		explicit operator std::list<double>() const {
			std::list<double> ans;
			for (int i = 0; i < n; ++i)
				ans.push_back(a[i]);
			return ans;
		}
		double at(int x) const {
			if (x < 0 || x >= n) {
				throw euclidean_vector_error("Index " + std::to_string(x)
				                             + " is not valid for this euclidean_vector object");
				return a[0];
			}
			return a[x];
		}
		double& at(int x) {
			if (x < 0 || x >= n) {
				throw euclidean_vector_error("Index " + std::to_string(x)
				                             + " is not valid for this euclidean_vector object");
				return a[0];
			}
			return a[x];
		}
		int dimensions() const {
			return n;
		}
		friend bool operator==(euclidean_vector const&, euclidean_vector const&);
		friend bool operator!=(euclidean_vector const&, euclidean_vector const&);
		friend euclidean_vector operator+(euclidean_vector const&, euclidean_vector const&);
		friend euclidean_vector operator-(euclidean_vector const&, euclidean_vector const&);
		friend euclidean_vector operator*(euclidean_vector const&, double);
		friend euclidean_vector operator/(euclidean_vector const&, double);
		friend std::ostream& operator<<(std::ostream&, euclidean_vector const&);
		friend auto euclidean_norm(euclidean_vector const& v) -> double;
		friend auto unit(euclidean_vector const& v) -> euclidean_vector;
		friend auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double;

	private:
		// ass2 spec requires we use double[]
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitude_;
		// TODO more if needed
		double a[20000];
		int n;
	};

	double euclidean_norm(euclidean_vector const& v);
	euclidean_vector unit(euclidean_vector const& v);
	double dot(euclidean_vector const& x, euclidean_vector const& y);
} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP