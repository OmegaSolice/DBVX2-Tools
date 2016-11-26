#pragma once
void ChangeSkill(LRESULT Name, LRESULT Costume, LRESULT SuperSkill[4], LRESULT UltimateSkill[2], LRESULT AwokenSkill, LRESULT EvasiveSkill, HWND EditError);
void GetSkill(LRESULT Name, LRESULT Costume, LRESULT SuperSkill[4], LRESULT UltimateSkill[2], LRESULT &AwokenSkill, LRESULT &EvasiveSkill, HWND EditError);
int LoadSkill(char File[MAX_PATH], std::string &Setting, SKILL *Skill);