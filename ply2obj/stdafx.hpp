// stdafx.hpp : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h
// �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h
// �t�@�C��
// ���L�q���܂��B
//

#pragma once

#ifndef _WIN32_WINNT  // Windows XP
                      // �ȍ~�̃o�[�W�����ɌŗL�̋@�\�̎g�p�������܂��B
#define _WIN32_WINNT \
  0x0501  // ����� Windows �̑��̃o�[�W���������ɓK�؂Ȓl�ɕύX���Ă��������B
#endif

#include <stdio.h>
#include <tchar.h>

// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă��������B
#include <rply.h>
#include <vector>