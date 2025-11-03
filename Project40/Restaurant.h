#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<Windows.h>

using namespace std;

void setColor(int textColor) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, textColor);
}


class Ingredient {
	string name;
	float quantity;
	float KgPrice;
public:
	Ingredient() {
		this->name = "";
		this->quantity = 0;
		this->KgPrice = 0;
	}
	Ingredient(string name, float quantity, float KgPrice) {
		this->name = name;
		this->quantity = quantity;
		this->KgPrice = KgPrice;
	}

	string GetName()const {
		return name;

	}
	float GetQuantity()const {
		return quantity;
	}
	float GetKgPrice()const {
		return KgPrice;
	}

	void SetQuantity(float quantity) {
		if (quantity >= 0) {
			this->quantity = quantity;
		}
		else {
			setColor(4);
			throw string("Quantity cannot be negative !");
			setColor(7);
		}
	}

	void SetKgPrice(float KgPrice) {
		if (KgPrice >= 0) {
			this->KgPrice = KgPrice;
		}
		else {
			setColor(4);
			throw string("Price cannot be negative !");
			setColor(7);
		}
	}

	void AddQuantity(float weight) {
		if (weight > 0) {
			quantity += weight;
		}
		else {
			setColor(4);
			throw string("The added quantity must be positive !");
			setColor(7);
		}
	}

	void RemoveQuantity(float weight) {
		if (weight > 0) {
			if (quantity >= weight) {
				quantity -= weight;
			}
			else {
				setColor(4);
				throw string("There is not enough quantity !");
				setColor(7);
			}
		}
		else {
			setColor(4);
			throw string("The quantity to be removed must be positive !");
			setColor(7);
		}
	}
	float TotalPrice()const {
		return quantity * KgPrice;
	}
};

class FoodIngredient {
	string name;
	float weight;

public:
	FoodIngredient() {
		this->name = "";
		this->weight = 0;
	}

	FoodIngredient(string name, float weight) {
		this->name = name;
		this->weight = weight;
	}

	string GetName() const {
		return name;
	}

	float GetWeight() const {
		return weight;
	}

	void SetName(string name) {
		this->name = name;
	}

	void SetWeight(float weight) {
		if (weight >= 0) {
			this->weight = weight;
		}
		else {
			setColor(4);
			throw string("Quantity cannot be negative !");
			setColor(7);
		}
	}
};

class Food {
	string name;
	string about;
	float price;
	vector<FoodIngredient> ingredients;

public:
	Food() {
		this->name = "";
		this->about = "";
		this->price = 0;
	}

	Food(string name, string about, float price) {
		this->name = name;
		this->about = about;
		this->price = price;
	}

	string GetName() const {
		return name;
	}
	string GetAbout() const {
		return about;
	}
	float GetPrice() const {
		return price;
	}

	const vector<FoodIngredient>& GetIngredients() const {
		return ingredients;
	}

	void SetName(string name) {
		this->name = name;
	}

	void SetAbout(string about) {
		this->about = about;
	}

	void SetPrice(float price) {
		if (price >= 0) {
			this->price = price;
		}
		else {
			setColor(4);
			throw string("Price cannot be negative !");
			setColor(7);
		}
	}

	void AddIngredient(string Ing_Name, float weight) {
		if (weight > 0) {
			ingredients.push_back(FoodIngredient(Ing_Name, weight));
		}
		else {
			setColor(4);
			throw string("Ingredient quantity must be positive !");
			setColor(7);
		}
	}

	void PrintIngredients() const {
		if (ingredients.empty()) {
			cout << "   Ingredients: None\n";
			return;
		}
		cout << "   Ingredients: ";
		for (size_t i = 0; i < ingredients.size(); i++) {
			cout << ingredients[i].GetName() << " (" << ingredients[i].GetWeight() << " kq)";
			if (i < ingredients.size() - 1) {
				cout << ", ";
			}
		}
		cout << endl;
	}

	float CostPrice(const vector<Ingredient>& stock) const {
		float totalCost = 0;
		for (size_t i = 0; i < ingredients.size(); i++) {
			for (size_t j = 0; j < stock.size(); j++) {
				if (ingredients[i].GetName() == stock[j].GetName()) {
					totalCost += ingredients[i].GetWeight() * stock[j].GetKgPrice();
					break;
				}
			}
		}
		return totalCost;
	}
};

class Restaurant {

	vector<Food> menu;
	vector<Ingredient> stock;
	vector<Food> cart;
	float budget;

public:
	Restaurant() {
		this->budget = 5000;
	}

	float GetBudget() const {
		return budget;
	}

	int GetMenuSize() const {
		return menu.size();
	}

	const Food& GetFood(size_t index) const {
		if (index >= menu.size()) {
			setColor(4);
			throw string("Invalid menu index !");
			setColor(7);
		}
		return menu[index];
	}

	void AddFood(const Food& food) {
		menu.push_back(food);
		setColor(10);
		cout << "The Food and ingredients have been added to the menu !\n";
		setColor(7);
	}

	void RemoveFood(string name) {
		for (size_t i = 0; i < menu.size(); i++) {
			if (menu[i].GetName() == name) {
				menu.erase(menu.begin() + i);
				setColor(10);
				cout << "The Food has been removed from the menu !\n";
				setColor(7);
				return;
			}
		}
		setColor(4);
		throw string("Food not found");
		setColor(7);
	}

	bool CheckIngredients(const Food& food) const {
		const vector<FoodIngredient>& ingredients = food.GetIngredients();
		for (size_t i = 0; i < ingredients.size(); i++) {
			bool found = false;
			for (size_t j = 0; j < stock.size(); j++) {
				if (ingredients[i].GetName() == stock[j].GetName() &&
					stock[j].GetQuantity() >= ingredients[i].GetWeight()) {
					found = true;
					break;
				}
			}
			if (!found) return false;
		}
		return true;
	}

	void RemoveIngredients(const Food& food) {
		const vector<FoodIngredient>& ingredients = food.GetIngredients();
		for (size_t i = 0; i < ingredients.size(); i++) {
			for (size_t j = 0; j < stock.size(); j++) {
				if (ingredients[i].GetName() == stock[j].GetName()) {
					stock[j].RemoveQuantity(ingredients[i].GetWeight());
					break;
				}
			}
		}
	}

	void AddIngredientToStock(const Ingredient& ingredient) {
		if (ingredient.GetQuantity() <= 0 || ingredient.GetKgPrice() <= 0) {
			setColor(4);
			throw string("Quantity/Price cannot be negative or zero !");
			setColor(7);
		}

		float totalCost = ingredient.GetQuantity() * ingredient.GetKgPrice();
		if (budget < totalCost) {
			setColor(4);
			throw string("Not enough budget to add this ingredient !");
			setColor(7);
		}

		for (size_t i = 0; i < stock.size(); i++) {
			if (stock[i].GetName() == ingredient.GetName()) {
				stock[i].AddQuantity(ingredient.GetQuantity());
				stock[i].SetKgPrice(ingredient.GetKgPrice());
				budget -= totalCost;
				setColor(10);
				cout << "Ingredient added to the stock !\n";
				setColor(7);
				return;
			}
		}
		stock.push_back(ingredient);
		budget -= totalCost;
		setColor(10);
		cout << "New ingredient added to the stock !\n";
		setColor(7);
	}

	void RemoveIngredientFromStock(string name) {
		for (size_t i = 0; i < stock.size(); i++) {
			if (stock[i].GetName() == name) {
				stock.erase(stock.begin() + i);
				setColor(10);
				cout << "Ingredient removed from the stock !\n";
				setColor(7);
				return;
			}
		}
		setColor(4);
		throw string("Ingredient not found !");
		setColor(7);
	}

	void PrintMenu() const {
		setColor(14);
		cout << "\nMenu:\n";
		setColor(7);
		bool hasAvailableFood = false;
		for (size_t i = 0; i < menu.size(); i++) {
			if (CheckIngredients(menu[i])) {
				hasAvailableFood = true;
				cout << i + 1 << ". " << menu[i].GetName() << " - ";
				cout << menu[i].GetPrice() << " AZN\n";
				cout << "   About: " << menu[i].GetAbout() << "\n";
				menu[i].PrintIngredients();
				cout << "\n";
			}
		}
		if (!hasAvailableFood) {
			setColor(9);
			cout << "No available food in menu at the moment.\n";
			setColor(7);
		}
	}

	void PrintStock() const {
		cout << "\nStock:\n";
		for (size_t i = 0; i < stock.size(); i++) {
			cout << i + 1 << ". " << stock[i].GetName() << " - "
				<< stock[i].GetQuantity() << " kq, "
				<< stock[i].GetKgPrice() << " AZN/kg\n";
		}
	}

	void AddFoodToCart(string name) {
		for (size_t i = 0; i < menu.size(); i++) {
			if (menu[i].GetName() == name) {
				if (CheckIngredients(menu[i])) {
					cart.push_back(menu[i]);
					setColor(10);
					cout << "Food added to the cart !\n";
					setColor(7);
				}
				else {
					setColor(4);
					throw string("Not enough ingredient !");
					setColor(7);
				}
				return;
			}
		}
		setColor(4);
		throw string("Food not found !");
		setColor(7);
	}

	void RemoveFoodFromCart(string name) {
		for (size_t i = 0; i < cart.size(); i++) {
			if (cart[i].GetName() == name) {
				cart.erase(cart.begin() + i);
				setColor(10);
				cout << "Food removed from the cart !\n";
				setColor(7);
				return;
			}
		}
		setColor(4);
		throw string("Food not found in the cart !");
		setColor(7);
	}

	void CompleteOrder() {
		if (cart.empty()) {
			setColor(4);
			throw string("The cart is empty !");
			setColor(7);
		}
		for (size_t i = 0; i < cart.size(); i++) {
			if (!CheckIngredients(cart[i])) {
				setColor(4);
				throw string("Not enough ingredient for: ");
				cout << cart[i].GetName();
				setColor(7);
			}
		}

		float totalPrice = 0;
		for (size_t i = 0; i < cart.size(); i++) {
			totalPrice += cart[i].GetPrice();
			RemoveIngredients(cart[i]);
		}

		cout << "\nOrder Information:\n";
		cout << "Total Price: " << totalPrice << " AZN\n";
		setColor(10);
		cout << "Order completed !\n";
		setColor(7);

		budget += totalPrice;
		cart.clear();
	}
};