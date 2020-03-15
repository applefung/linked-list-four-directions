
/*
 * todo.cpp
 *
 *  Created on: Oct 31, 2018
 *      Author: kevinw
 */
#include "matrix.h"



/**
 * Important Notes:
 *
 * 1) All the code that you have written should be in this file.
 * 2) You can add any helper functions. And we suggest you to do it.
 * 3) Global varibles are not allowed, regardless of whether it is const or non const.
 * 4) Two class member functions, namely, print and debug, have been written for you in helper.cpp
 *    and you should not move these two function here, nor reimplement it.
 * 5) You can modify the main function for testing purpose. However, you should also
 *    expect that we will modify the main function when we grade your assignment.
 *
 *
 * If it crashes, take a deep breath.
 *
 */


/*
 * TODO: Constructor of the Matrix class
 * Hint: 1) Remember to initial all data members; if you don't know what values to be used, put nullptr or 0 first.
 *       2) You need to create dynamic Element objects in the constructor. As mentioned in the .h file,
 *          you need to create it using the syntax:
 *              Element* dynamicObject = new Element{nullptr, nullptr, nullptr, nullptr, id};
 *       3) You are advised to create some helper global functions to help you to do this task.
*/

Matrix::Matrix(int Height, int Width)
{
	height=Height;
	width=Width;
	Element* pnew[height][width];
	//width*height-i*width-k
	for(int i=0; i<Height; i++)
	{
		for(int k=0; k<Width; k++)
		{
			pnew[i][k]=new Element{nullptr, nullptr, nullptr, nullptr, 1+width*i+k};
		}
	}
	for(int i=0; i<Height; i++)
	{
		for(int k=0; k<Width; k++)
		{
			if(k==(Width-1))
			{
				pnew[i][k]->right=pnew[i][0];
			}
			else
			{
				pnew[i][k]->right=pnew[i][k+1];
			}
			if(k==0)
			{
				pnew[i][k]->left=pnew[i][Width-1];
			}
			else
			{
				pnew[i][k]->left=pnew[i][k-1];
			}
			if(i==(Height-1))
			{
				pnew[i][k]->down=pnew[0][k];
			}
			else
			{
				pnew[i][k]->down=pnew[i+1][k];
			}
			if(i==0)
			{
				pnew[i][k]->up=pnew[Height-1][k];
			}
			else
			{
				pnew[i][k]->up=pnew[i-1][k];
			}
		}
		for(int j=0; j<Width; j++)
		{
			colHeads[j]=pnew[0][j];
		}
		rowHeads[i]=pnew[i][0];
	}//initialize the pointers to null pointers and assign 0 to id*/
}



/*
 * TODO: isReverse() of the Matrix class
 * Hint: This should be a easier task, comparing with the others. Try to do it after the constructor is implemented.
 *
 */
bool Matrix::isReverse()	const
{
	int i=0, j=0;
	int memory=0;
	int memory_head=0;
	Element* prow;
	int count=0;
	if(height==1 && width==1)
	{
		return true;
	}
	if(height==1)
	{
		prow=colHeads[0];
		for(int a=0; a<(width-1); a++)
		{
			memory_head=prow->id;
			memory=colHeads[a+1]->id;
			if(memory_head-memory==1)
			{
				prow=prow->right;
				count+=1;
			}
		}
		if(count==width-1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if(width==1)
	{
		prow=rowHeads[0];
		for(int a=0; a<(height-1); a++)
		{
			memory_head=prow->id;
			memory=rowHeads[a+1]->id;
			if(memory_head-memory==1)
			{
				prow=prow->right;
				count+=1;
			}
			else
			{
				return false;
			}
		}
		if(count==height-1)
		{
			return true;
		}
	}
	for(; i<height; i++)
	{
		prow=rowHeads[i];
		for(; j<(width-1); j++)
		{
			if(j==0)
			{
				memory_head=rowHeads[i+1]->id;
			}
			if(j==(width-2))
			{
				memory=prow->right->id;
			}
			if(rowHeads[i]->id<rowHeads[i]->right->id)
			{
				return false;
			}
			if((prow->id)-(prow->right->id)==1)
			{
				prow=prow->right;
			}
			else
			{
				return false;
			}
		}
		if(memory-memory_head != 1)
		{
			return false;
		}
	}
	if(i*j==(width-1)*height)
	{
		return true;
	}
}

/*
 * TODO: reverseRow() of the Matrix class
 * Hint: This is not supposed to be simple and easy if you are not using recursion.
 */

void Matrix::reverseRow(int n)
{
	Element* previous=nullptr;//remember the previous one
	Element* current=rowHeads[n];
	Element* next;
	do
	{
		next=current->right;
		current->right=previous;
		previous=current;
		current=next;
	}while(current != rowHeads[n]);
	rowHeads[n]->right=previous;
	rowHeads[n]=previous;

	Element* pnew[height][width];
	Element* ptemp[height];
	Element* mem;
	for(int i=0; i<height; i++)
	{
		ptemp[i]=rowHeads[i];
	}
	for(int a=0; a<height; a++)
	{
		mem=ptemp[a];
		for(int b=0; b<width; b++)
		{
			pnew[a][b]=mem;
			mem=mem->right;

		}
	}
	for(int i=0; i<height; i++)
	{
		for(int k=0; k<width; k++)
		{
			if(k==(width-1))
			{
				pnew[i][k]->right=pnew[i][0];
			}
			else
			{
				pnew[i][k]->right=pnew[i][k+1];
			}
			if(k==0)
			{
				pnew[i][k]->left=pnew[i][width-1];
			}
			else
			{
				pnew[i][k]->left=pnew[i][k-1];
			}
			if(i==(height-1))
			{
				pnew[i][k]->down=pnew[0][k];
			}
			else
			{
				pnew[i][k]->down=pnew[i+1][k];
			}
			if(i==0)
			{
				pnew[i][k]->up=pnew[height-1][k];
			}
			else
			{
				pnew[i][k]->up=pnew[i-1][k];
			}
		}
		for(int c=0; c<width; c++)
		{
			colHeads[c]=pnew[0][c];
		}
	}
}


/*
 * TODO: circularShift() of the Matrix class
 * Hint: 1) You might first split this function into two parts, UP/DOWN and LEFT/RIGHT.
 * 	 2) Remember to update both horizontal linked list and vertical linked list.
 *
 */
void Matrix::circularShift(Direction x, int n)
{
	Element* ptemp_for_row=rowHeads[n];
	Element* memory_for_row=rowHeads[n];
	Element* ptemp_for_col=colHeads[n];
	Element* memory_for_col=colHeads[n];
	if(x==RIGHT)
	{
		for(int i=0; i<width; i++)
		{
			memory_for_row=rowHeads[n];
			rowHeads[n]=rowHeads[n]->right;
			rowHeads[n]->right=ptemp_for_row->right->right;
			rowHeads[n]->left=ptemp_for_row;
			ptemp_for_row=rowHeads[n];
		}
		rowHeads[n]=memory_for_row;
		Element* pnew[height][width];
		Element* ptemp[height];
		Element* mem;
		for(int i=0; i<height; i++)
		{
			ptemp[i]=rowHeads[i];
		}
		for(int a=0; a<height; a++)
		{
			mem=ptemp[a];
			for(int b=0; b<width; b++)
			{
				pnew[a][b]=mem;
				mem=mem->right;

			}
		}
		for(int i=0; i<height; i++)
		{
			for(int k=0; k<width; k++)
			{
				if(k==(width-1))
				{
					pnew[i][k]->right=pnew[i][0];
				}
				else
				{
					pnew[i][k]->right=pnew[i][k+1];
				}
				if(k==0)
				{
					pnew[i][k]->left=pnew[i][width-1];
				}
				else
				{
					pnew[i][k]->left=pnew[i][k-1];
				}
				if(i==(height-1))
				{
					pnew[i][k]->down=pnew[0][k];
				}
				else
				{
					pnew[i][k]->down=pnew[i+1][k];
				}
				if(i==0)
				{
					pnew[i][k]->up=pnew[height-1][k];
				}
				else
				{
					pnew[i][k]->up=pnew[i-1][k];
				}
			}
			for(int c=0; c<width; c++)
			{
				colHeads[c]=pnew[0][c];
			}
		}
	}
	else if(x==LEFT)
	{
		for(int i=0; i<width; i++)
		{
			memory_for_row=rowHeads[n];
			rowHeads[n]=rowHeads[n]->left;
			rowHeads[n]->left=ptemp_for_row->left->left;
			rowHeads[n]->right=ptemp_for_row;
			ptemp_for_row=rowHeads[n];
		}
		rowHeads[n]=memory_for_row;
		Element* pnew[height][width];
		Element* ptemp[height];
		Element* mem;
		for(int i=0; i<height; i++)
		{
			ptemp[i]=rowHeads[i];
		}
		for(int a=0; a<height; a++)
		{
			mem=ptemp[a];
			for(int b=0; b<width; b++)
			{
				pnew[a][b]=mem;
				mem=mem->right;

			}
		}
		for(int i=0; i<height; i++)
		{
			for(int k=0; k<width; k++)
			{
				if(k==(width-1))
				{
					pnew[i][k]->right=pnew[i][0];
				}
				else
				{
					pnew[i][k]->right=pnew[i][k+1];
				}
				if(k==0)
				{
					pnew[i][k]->left=pnew[i][width-1];
				}
				else
				{
					pnew[i][k]->left=pnew[i][k-1];
				}
				if(i==(height-1))
				{
					pnew[i][k]->down=pnew[0][k];
				}
				else
				{
					pnew[i][k]->down=pnew[i+1][k];
				}
				if(i==0)
				{
					pnew[i][k]->up=pnew[height-1][k];
				}
				else
				{
					pnew[i][k]->up=pnew[i-1][k];
				}
			}
			for(int c=0; c<width; c++)
			{
				colHeads[c]=pnew[0][c];
			}
		}
	}
	else if(x==UP)
	{
		for(int i=0; i<height; i++)
		{
			memory_for_col=colHeads[n];
			colHeads[n]=colHeads[n]->up;
			colHeads[n]->up=ptemp_for_col->up->up;
			colHeads[n]->down=ptemp_for_col;
			ptemp_for_col=colHeads[n];
		}
		colHeads[n]=memory_for_col;
		Element* pnew[height][width];
		Element* ptemp[width];
		Element* mem;
		for(int i=0; i<width; i++)
		{
			ptemp[i]=colHeads[i];
		}
		for(int a=0; a<width; a++)
		{
			mem=ptemp[a];
			for(int b=0; b<height; b++)
			{
				pnew[b][a]=mem;
				mem=mem->down;
			}
		}
		for(int i=0; i<height; i++)
		{
			for(int k=0; k<width; k++)
			{
				if(k==(width-1))
				{
					pnew[i][k]->right=pnew[i][0];
				}
				else
				{
					pnew[i][k]->right=pnew[i][k+1];
				}
				if(k==0)
				{
					pnew[i][k]->left=pnew[i][width-1];
				}
				else
				{
					pnew[i][k]->left=pnew[i][k-1];
				}
				if(i==(height-1))
				{
					pnew[i][k]->down=pnew[0][k];
				}
				else
				{
					pnew[i][k]->down=pnew[i+1][k];
				}
				if(i==0)
				{
					pnew[i][k]->up=pnew[height-1][k];
				}
				else
				{
					pnew[i][k]->up=pnew[i-1][k];
				}
			}
			for(int c=0; c<height; c++)
			{
				rowHeads[c]=pnew[c][0];
			}
		}
	}
	else if(x==DOWN)
	{
		for(int i=0; i<height; i++)
		{
			memory_for_col=colHeads[n];
			colHeads[n]=colHeads[n]->down;
			colHeads[n]->down=ptemp_for_col->down->down;
			colHeads[n]->up=ptemp_for_col;
			ptemp_for_col=colHeads[n];
		}
		colHeads[n]=memory_for_col;
		Element* pnew[height][width];
		Element* ptemp[width];
		Element* mem;
		for(int i=0; i<width; i++)
		{
			ptemp[i]=colHeads[i];
		}
		for(int a=0; a<width; a++)
		{
			mem=ptemp[a];
			for(int b=0; b<height; b++)
			{
				pnew[b][a]=mem;
				mem=mem->down;
			}
		}
		for(int i=0; i<height; i++)
		{
			for(int k=0; k<width; k++)
			{
				if(k==(width-1))
				{
					pnew[i][k]->right=pnew[i][0];
				}
				else
				{
					pnew[i][k]->right=pnew[i][k+1];
				}
				if(k==0)
				{
					pnew[i][k]->left=pnew[i][width-1];
				}
				else
				{
					pnew[i][k]->left=pnew[i][k-1];
				}
				if(i==(height-1))
				{
					pnew[i][k]->down=pnew[0][k];
				}
				else
				{
					pnew[i][k]->down=pnew[i+1][k];
				}
				if(i==0)
				{
					pnew[i][k]->up=pnew[height-1][k];
				}
				else
				{
					pnew[i][k]->up=pnew[i-1][k];
				}
			}
			for(int c=0; c<height; c++)
			{
				rowHeads[c]=pnew[c][0];
			}
		}
	}

}


/*
 * TODO: Destructor of the Matrix class
 * Hint: 1) Leave this task to the very end of your assignment. The worst case is you don't pick up the
 * 	    memory leak point. Fail to do this will not affect the correctness of your program output.
 * 	    However, if you do it wrongly, your program may crash.
 *
 */
Matrix::~Matrix()
{
	Element* current_for_col;
	Element* ptemp_for_col;
	for(int i=width-1; i>=0; i--)
	{
		current_for_col=colHeads[i]->down;
		while(current_for_col->down != colHeads[i]->down)
		{
			ptemp_for_col=current_for_col;
			current_for_col=current_for_col->down;
			delete ptemp_for_col;
		}
		delete current_for_col;
	}
};






