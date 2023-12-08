#include "SonikBaundaryBlock.h"

namespace SonikBaundaryBlock
{

	//==================================================================================
	//					�O�u�^�O
	//==================================================================================
	//�R���X�g���N�^
	SonikBaundaryPre::SonikBaundaryPre(void)
	:UseUserMemorySize(0)
	,Flag(0)
	,RefCounter(0)
	,freelist_next(0)
	,freelist_prev(0)
	{
		//���������B

	};

	//�R�s�[�R���X�g���N�^�B�R�s�[�̋֎~�B
	SonikBaundaryPre::SonikBaundaryPre(SonikBaundaryPre& t_his)
	:UseUserMemorySize(0)
	,Flag(0)
	,RefCounter(0)
	,freelist_next(0)
	,freelist_prev(0)
	{
		//���������B
	};

	//�f�X�g���N�^
	SonikBaundaryPre::~SonikBaundaryPre(void)
	{
		//���������B
		//����new���Ńq�[�v�������Ă�킯�ł͂Ȃ��̂ŁB
	}

	//������Z�q�B�R�s�[�y�ё�������̋֎~
	SonikBaundaryPre& SonikBaundaryPre::operator =(SonikBaundaryPre& t_his)
	{
		//���������B

		return (*this);
	}

	//placement new
	void* SonikBaundaryPre::operator new(std::size_t size, void* ptr)
	{
		return ptr;
	};

	//placement delete
	void SonikBaundaryPre::operator delete(void* ptr_new, void* heepPtr)
	{
		//���������B
	}
	//�f�t�H���gdelete �̃I�[�o�[���[�h�B���ꂪ�Ȃ��ƌx���Ƃ�VC�œf����邻���ȁB
	void SonikBaundaryPre::operator delete(void* ptr)
	{
		//���������B
	};

	//���݂̈ʒu�����u�^�O�܂ł̃T�C�Y���擾����B
	unsigned long SonikBaundaryPre::GetGoPostTagSize(void)
	{
		return ( sizeof(SonikBaundaryPre) + UseUserMemorySize );
	};

	//���݂̉^�p������(���[�U�[�g�p������)�T�C�Y���擾����B
	unsigned long SonikBaundaryPre::GetUseMemorySize(void)
	{
		return UseUserMemorySize;
	};

	//���݂̈ʒu�����u�^�O���܂ނ��ׂẴT�C�Y���擾����B
	unsigned long SonikBaundaryPre::GetAllDataSize(void)
	{
		return ( sizeof(SonikBaundaryPre) + UseUserMemorySize + sizeof(SonikBaundaryPost) );
	};

	//���݂̉^�p������(���[�U�[�g�p������)���g�p�����ǂ����̃t���O���擾����B
	bool SonikBaundaryPre::GetUsedFlag(void)
	{
		return Flag;
	};

	//�^�p�������T�C�Y��ݒ肷��B
	//����1: �Z�b�g����^�p�������T�C�Y���w�肵�܂��B
	void SonikBaundaryPre::SetUseUserMemorySize(unsigned long SetSize)
	{
		UseUserMemorySize = SetSize;
	};

	//�^�p��ԃt���O��ݒ肷��B
	//����1: �g�p��Ԃ�\���ꍇ�́Atrue, ���g�p��Ԃ�\���ꍇ�ɂ�false ��ݒ肵�܂��B
	void SonikBaundaryPre::SetUseFlag(bool SetFlag)
	{
		Flag = SetFlag;
	};

	//==================================================================================
	//					��u�^�O
	//==================================================================================
	//�R���X�g���N�^
	SonikBaundaryPost::SonikBaundaryPost(void)
	:PrePointer(0)
	{

	};

	//�R�s�[�R���X�g���N�^�B�R�s�[�̋֎~
	SonikBaundaryPost::SonikBaundaryPost(SonikBaundaryPost& t_his)
	:PrePointer(0)
	{
		//���������B
	};

	//�f�X�g���N�^
	SonikBaundaryPost::~SonikBaundaryPost(void)
	{
		//���������B
		//����new���Ńq�[�v�������Ă�킯�ł͂Ȃ��̂ŁB
	};

	//������Z�q�I�[�o�[���[�h�B����ƃR�s�[�̋֎~
	SonikBaundaryPost& SonikBaundaryPost::operator = (SonikBaundaryPost& t_his)
	{
		//���������B
		return (*this);
	};

	//placement new
	void* SonikBaundaryPost::operator new(std::size_t size, void* ptr)
	{
		return ptr;
	};

	//placement delete
	void SonikBaundaryPost::operator delete(void* ptr_new, void* heepPtr)
	{
		//���������B
	};
	//�f�t�H���gdelete �̃I�[�o�[���[�h�B���ꂪ�Ȃ��ƌx���Ƃ�VC�œf����邻���ȁB
	void SonikBaundaryPost::operator delete(void* ptr)
	{
		//���������B
	};

	//���݂̈ʒu����O�u�^�O�̃|�C���^���擾����B
	SonikBaundaryPre* SonikBaundaryPost::GetGoPreTagPtr(void)
	{
		return PrePointer;
	};

	//�O�u�^�O�ւ̃|�C���^���Z�b�g���܂��B
	void SonikBaundaryPost::SetPrePointer(SonikBaundaryPre* SetPointer)
	{
		PrePointer = SetPointer;
	};


}
