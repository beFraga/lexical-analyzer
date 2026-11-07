#include "LexicalTree.h"
#include <stack>
#include <algorithm>
#include <iostream>

LexicalTree::LexicalTree(const std::string & re) : _re(re), root(nullptr), leaf_counter(1) {
	_re = "(" + _re + ")#";
	generate_tree();
}

LexicalTree::~LexicalTree() {
	destroy_tree(root);
}

void LexicalTree::destroy_tree(Node * node) {
	if (!node) return;
	destroy_tree(node->l);
	destroy_tree(node->r);
	delete node;
}

std::string expand_groups(const std::string & re) {
	//TODO
}

std::string LexicalTree::insert_explicit_concat(const std::string & re) {
	std::string res = "";
	for (size_t i = 0; i < re.size(); i++) {
		res += re[i];
		if (i + 1 >= re.size()) continue;

		char c1 = re[i];
		char c2 = re[i + 1];
		bool is_c1_val = (c1 != '(' && c1 != '|' && c1 != '.');
		bool is_c2_val = (c2 != ')' && c2 != '|' && c2 != '.' && c2 != '*' && c2 != '+' && c2 != '?');
		if (is_c1_val && is_c2_val) res += '.';
	}

	return res;
}

int LexicalTree::precedence(char c) {
	if (c == '*' || c == '+' || c == '?') return 3;
	if (c == '.') return 2;
	if (c == '|') return 1;
	return 0;
}

std::string LexicalTree::infix_to_postfix(const std::string & re) {
	std::string postfix = "";
	std::stack<char> st;

	for (auto c : re) {
		if (c == '*' || c == '+' || c == '?' || c == '.' || c == '|' || c == '(' || c == ')') {
			if (c == '(')
				st.push(c);
			else if (c == ')') {
				while (!st.empty() && st.top() != '(') {
					postfix += st.top();
					st.pop();
				}
				if (!st.empty()) st.pop(); // Only one (
			} else  {
				while (!st.empty() && precedence(st.top()) >= precedence(c)) {
					postfix += st.top();
					st.pop();
				}
				st.push(c);
			}
		} else  {
			postfix += c;
		}
	}

	while (!st.empty()) {
		postfix += st.top();
		st.pop();
	}
	return postfix;
}


void LexicalTree::generate_tree() {
	std::cout << "Starting formating.." << std::endl;
	std::string exp_re = insert_explicit_concat(_re);
	std::string postfix = infix_to_postfix(exp_re);

	std::stack<Node *> st;

	auto safe_pop = [&st]() -> Node * {
		if (st.empty()) {
			std::cerr << "Fatal error: Bad format." << std::endl;
			exit(1);
		}
		Node * n = st.top();
		st.pop();
		return n;
	};
	std::cout << "Generating tree.." << std::endl;

	for (auto c : postfix) {
		if (c == '*' || c == '+' || c == '?') {
			NodeT type = (c == '*') ? NodeT::STAR : (c == '+' ? NodeT::CROSS : NodeT::OPT);
			Node * n = new Node(type, std::string(1, c));
			n->l = safe_pop();
			st.push(n);
		} else if (c == '.' || c == '|') {
			NodeT type = (c == '.') ? NodeT::CAT : NodeT::OR;
			Node * n = new Node(type, std::string(1, c));
			n->r = safe_pop();
			n->l = safe_pop();
			st.push(n);
		} else {
			Node * n = new Node(NodeT::VALUE, std::string(1, c), leaf_counter++);
			st.push(n);
		}
	}

	root = st.top();
	std::cout << "Computing sets.." << std::endl;
	compute_sets(root);
}

void LexicalTree::compute_sets(Node * node) {
	if (!node) return;

	compute_sets(node->l);
	compute_sets(node->r);
	
	if (node->type == NodeT::VALUE) {
		// We need to calculate epsilon?
		node->nullable = false;
		node->firstpos.insert(node->id);
		node->lastpos.insert(node->id);
	}
	else if (node->type == NodeT::OR) {
		node->nullable = node->l->nullable || node->r->nullable;

		node->firstpos.insert(node->l->firstpos.begin(), node->l->firstpos.end());
		node->firstpos.insert(node->r->firstpos.begin(), node->r->firstpos.end());

		node->lastpos.insert(node->l->lastpos.begin(), node->l->lastpos.end());
		node->lastpos.insert(node->r->lastpos.begin(), node->r->lastpos.end());
	}
	else if (node->type == NodeT::CAT) {
		node->nullable = node->l->nullable && node->r->nullable;

		node->firstpos.insert(node->l->firstpos.begin(), node->l->firstpos.end());
		if (node->l->nullable)
			node->firstpos.insert(node->r->firstpos.begin(), node->r->firstpos.end());

		node->lastpos.insert(node->r->lastpos.begin(), node->r->lastpos.end());
		if (node->r->nullable)
			node->lastpos.insert(node->l->lastpos.begin(), node->l->lastpos.end());
	}
	else if (node->type == NodeT::STAR || node->type == NodeT::OPT) {
		node->nullable = true;

		node->firstpos.insert(node->l->firstpos.begin(), node->l->firstpos.end());
		node->lastpos.insert(node->l->lastpos.begin(), node->l->lastpos.end());
	}
	else if (node->type == NodeT::CROSS) {
		node->nullable = node->l->nullable;

		node->firstpos.insert(node->l->firstpos.begin(), node->l->firstpos.end());
		node->lastpos.insert(node->l->lastpos.begin(), node->l->lastpos.end());

	}
}
