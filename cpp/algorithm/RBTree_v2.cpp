/*
* RBTree_v2.cpp
*
*  Created on: Dec 25, 2014
*      Author: from houjie's the annotated stl sources
*/
#include <stddef.h>
#include <bits/allocator.h>
#include <bits/stl_iterator_base_types.h>

typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;
const __rb_tree_color_type __rb_tree_black = true;

struct __rb_tree_node_base
{
	typedef __rb_tree_color_type color_type;
	typedef __rb_tree_node_base* base_ptr;

	color_type color;
	base_ptr parent;
	base_ptr left;
	base_ptr right;

	static base_ptr minimum(base_ptr x)
	{
		while(x->left != 0)
			x = x->left;
		return x;
	}

	static base_ptr maximum(base_ptr x)
	{
		while(x->right != 0)
			x = x->right;
		return x;
	}
};

template <typename Value>
struct __rb_tree_node : public __rb_tree_node_base
{
	typedef __rb_tree_node<Value>* link_type;
	Value value_field;
};

struct __rb_tree_base_iterator
{
	typedef __rb_tree_node_base::base_ptr base_ptr;
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;
	base_ptr node;

	void increment()
	{
		if (node->right != 0)
		{
			node = node->right;
			while (node->left != 0)
				node = node->left;
		}
		else
		{
			base_ptr y = node->parent;
			while (node == y->right)
			{
				node = y;
				y = y->parent;
			}

			if (node->right != y)
				node = y;
		}
	}

	void decrement()
	{
		if (node->color == __rb_tree_red &&
			node->parent->parent == node)
		{
			node = node->right;
		}
		else if (node->left != 0)
		{
			base_ptr y = node->left;
			while (y->right != 0)
				y = y->right;
			node = y;
		}
		else
		{
			base_ptr y = node->parent;
			while (node == y->left) {
				node = y;
				y = y->parent;
			}
			node = y;
		}
	}
};

template <typename Value, typename Ref, typename Ptr>
struct __rb_tree_iterator : public __rb_tree_base_iterator
{
	typedef Value value_type;
	typedef Ref reference;
	typedef Ptr pointer;
	typedef __rb_tree_iterator<Value, Value&, Value*> iterator;
	typedef __rb_tree_iterator<Value, const Value&, const Value*> const_iterator;
	typedef __rb_tree_iterator<Value, Ref, Ptr> self;
	typedef __rb_tree_node<Value>* link_type;

	__rb_tree_iterator() {}
	__rb_tree_iterator(link_type x) { node = x; }
	__rb_tree_iterator(const iterator& it) { node = it.node; }

	reference operator*() const
	{
		return link_type(node)->value_field;
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	self& operator++()
	{
		increment();
		return *this;
	}

	self operator++(int)
	{
		self tmp = *this;
		increment();
		return tmp;
	}

	self& operator--()
	{
		decrement();
		return *this;
	}

	self operator--(int)
	{
		self tmp = *this;
		decrement();
		return tmp;
	}
};

template<typename Key, typename Value, typename KeyOfValue,
		 typename Compare, typename Alloc = std::allocator<Value>>
class rb_tree
{
protected:
	typedef void* void_pointer;
	typedef __rb_tree_node_base* base_ptr;
	typedef __rb_tree_node<Value> rb_tree_node;
	typedef typename Alloc::template rebind<__rb_tree_node<Value>>::other
			rb_tree_node_alloctor;
	typedef __rb_tree_color_type color_type;

public:
	typedef Key key_type;
	typedef Value value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef rb_tree_node* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
protected:
	link_type get_node()
	{
		return rb_tree_node_alloctor::allocate();
	}

	link_type put_node(link_type p)
	{
		return rb_tree_node_alloctor::deallocator(p);
	}

	link_type create_node(const value_type& x)
	{
		link_type tmp = get_node();
		//ignore initialize

		return tmp;
	}

	link_type clone_node(link_type x)
	{
		link_type tmp = create_node(x->value_field);
		tmp->color = x->color;
		tmp->left = 0;
		tmp->right = 0;
		return tmp;
	}

	void destroy_node(link_type p)
	{
		destroy(&p->value_filed);
		put_node(p);
	}

protected:
	size_type node_count;
	link_type header;
	Compare key_compare;

	link_type& root() const
	{
		return (link_type&)header->parent;
	}

	link_type& leftmost() const
	{
		return (link_type&)header->left;
	}

	link_type& rightmost() const
	{
		return (link_type&)header->right;
	}

	static link_type& left(link_type x)
	{
		return (link_type&)(x->left);
	}

	static link_type& right(link_type x)
	{
		return (link_type&)(x->right);
	}

	static link_type& parent(link_type x)
	{
		return (link_type&)(x->parent);
	}

	static color_type& color(link_type x)
	{
		return (color_type&)(link_type(x)->color);
	}

	//....ellipsis

	static link_type minimum(link_type x)
	{
		return (link_type) __rb_tree_node_base::minimum(x);
	}

	static link_type maximum(link_type x)
	{
		return (link_type) __rb_tree_node_base::maximum(x);
	}

public:
	typedef __rb_tree_iterator<value_type, reference, pointer> iterator;

private:
	iterator __insert(base_ptr x, base_ptr y, const value_type& v);
	link_type __copy(link_type x, link_type p);
	void __erase(link_type x);
	void init()
	{
		header = get_node();
		color(header) = __rb_tree_red;
		root() = 0;
		leftmost() = header;
		rightmost() = header;
	}

public:
	rb_tree(const Compare& comp = Compare())
		: node_count(0), key_compare(comp)
	{
		init();
	}

	~rb_tree()
	{
		//clear();
		put_node(header);
	}

	rb_tree<Key, Value, KeyOfValue, Compare, Alloc>&
		operator=(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x);

public:
	Compare key_comp() const
	{
		return key_compare;
	}

	iterator begin()
	{
		return leftmost();
	}

	iterator end()
	{
		return header;
	}

	bool empty() const
	{
		return node_count == 0;
	}

	size_type size() const
	{
		return node_count;
	}

	size_type max_size() const
	{
		return size_type(-1);
	}

public:
	std::pair<iterator, bool> insert_unique(const value_type& x);
	iterator insert_equal(const value_type& x);

	//...
};

template<typename Key, typename Value, typename KeyOfValue,
		 typename Compare, typename Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(const Value& v)
{
	link_type y = header;
	link_type x = root();
	while (x != 0)
	{
		y = x;
		x = key_compare(KeyOfValue()(v), key(x)) ? left(x) : right(x);
	}

	return __insert(x, y, v);
}

template<typename Key, typename Value, typename KeyOfValue,
		 typename Compare, typename Alloc>
std::pair<typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator, bool>
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(const Value& v)
{
	link_type y = header;
	link_type x = root();
	bool comp = true;
	while (x != 0) {
		y = x;
		comp = key_compare(KeyOfValue()(v), key(x));
		x = comp ? left(x) : right(x);
	}

	iterator j = iterator(y);
	if (comp)
		if (j == begin())
			return pair<iterator, bool>(__insert(x, y, v), true);
		else
			--j;

	if (key_compare(key(j.node), KeyOfValue()(v)))
		return pair<iterator, bool>(__insert(x, y, v), true);

	return pair<iterator, bool>(j, false);
}

template<typename Key, typename Value, typename KeyOfValue,
		 typename Compare, typename Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::__insert(base_ptr x_,
														  base_ptr y_,
														  const Value& v)
{
	link_type x = (link_type) x_;
	link_type y = (link_type) y_;
	link_type z;

	if (y == header || x != 0 || key_compare(KeyOfValue()(v), key(y)))
	{
		z = create_node(v);
		left(y) = z;
		if (y == header)
		{
			root() = z;
			rightmost() = z;
		}
		else if (y == leftmost())
			leftmost() = z;

	}
	else
	{
		z = create_node(v);
		right(y) = z;
		if (y == rightmost())
			rightmost() = z;
	}

	parent(z) = y;
	left(z) = 0;
	right(z) = 0;

	__rb_tree_rebalance(z, header->parent);
	++node_count;
	return iterator(z);
}

inline void
__rb_tree_rotate_left(__rb_tree_node_base* x, __rb_tree_node_base*& root)
{

}

inline void
__rb_tree_rotate_right(__rb_tree_node_base* x, __rb_tree_node_base*& root)
{

}

inline void
__rb_tree_rebalance(__rb_tree_node_base* x, __rb_tree_node_base*& root)
{
	x->color = __rb_tree_red;
	while (x != root && x->parent->color == __rb_tree_red)
	{
		if (x->parent == x->parent->parent->left)
		{
			__rb_tree_node_base* y = x->parent->parent->right;
			if (y && y->color == __rb_tree_red)
			{
				x->parent->color = __rb_tree_black;
				y->color = __rb_tree_black;
				x->parent->parent->color = __rb_tree_red;
				x = x->parent->parent;
			}
			else
			{
				if (x == x->parent->right)
				{
					x = x->parent;
					__rb_tree_rotate_left(x, root);
				}

				x->parent->color = __rb_tree_black;
				x->parent->parent->color = __rb_tree_red;
				__rb_tree_rotate_right(x->parent->parent, root);
			}
		}
		else
		{

		}
	}
}

int main()
{
	return 0;
}
