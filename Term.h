#ifndef Term_h
#define Term_h

template <class Type>
class Term
{
private:
	Type m_term;
public:
	Term(Type term)
	{
		m_term=term;
	};
};

#endif