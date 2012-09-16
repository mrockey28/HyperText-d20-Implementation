#include <iostream>
#include "Beings\character.h"
#include "stdio.h"
#include "stdlib.h"
#include "Beings\enemy.h"
#include "battle.h"
#include "rpgUtils.h"

char getch()
{
	char output;
	output = getchar();
	if (output != '\n')
	{
		getchar();
	}

	return output;
}

void Battle::MainBattleMenu()
{
	printf("You are %d meters from the %s!\n", distanceToEnemy, (enemy.GetName()).c_str());
	printf("Select an option:\n");
	printf("f - Run forward			e - Go to backpack\n");
	printf("b - Go backwards		d - Draw equipped weapon\n");
	printf("m - Use melee weapon		r - Use ranged weapon\n");
	printf("g - Use magic			u - Run away\n");		
}

char Battle::GetMainMenuSelection()
{
	char menuChoice = '\0';

	while (!IsValidMainMenuOption(menuChoice))
	{
		menuChoice = getch();
	}
	return menuChoice;
}

bool Battle::IsValidMainMenuOption(char i)
{
	if (i == 'f' || i == 'e' || i == 'b' || i == 'd' || 
		i == 'm' || i == 'r' || i == 'g' || i == 'u')
	{
		return TRUE;
	}
	return FALSE;
}

bool Battle::MainMenuSwitcher(char menuChoice)
{

	switch(menuChoice)
	{
		case 'f':
			return RunForward();
		case 'b':
			return GoBackwards();
		case 'e':
			return BackpackMenu();
		case 'd':
			return DrawWeapon();
		case 'm':
			return UseMeleeWeapon();
		case 'r':
			return UseRangedWeapon();
		case 'g':
			return MagicMenu();
		case 'u':
			return RunAway();
		default:
			printf("ERROR: MainMenuSwitcher was passed '%c'! This should never happen!\n", menuChoice);
			return FALSE;
	}
}
	bool Battle::RunForward(){return FALSE;}
	bool Battle::GoBackwards(){return FALSE;}
	bool Battle::BackpackMenu(){return FALSE;}
	bool Battle::DrawWeapon(){return FALSE;}
	bool Battle::UseMeleeWeapon(){return FALSE;}
	bool Battle::UseRangedWeapon(){return FALSE;}
	bool Battle::MagicMenu(){return FALSE;}

bool Battle::RunAway()
{
	
	if (enemy.GetBossFlag())
	{
		printf("You can't run from a boss battle!\n");
		return FALSE;
	}
	if (playerMoves != playerMaxMoves)
	{
		printf("You can't run unless you have all your moves left!");
		return FALSE;
	}
	SpendMoves(playerMaxMoves);
	
	if ((Xd6(9) + (uint16)enemy.GetSpeed()) >= (Xd6(10)+(uint16)player.GetAgilityMod()))
	{
		printf("You failed  to escape.\n");
		return TRUE;
	}
	printf("You ran from the battle!\n");
	battleFled = TRUE;
	return TRUE;
}

void setExtraInfo(PlayerCharacter* player, EnemyHumanoid* enemy)
{
	player->SetStrength(20);
	enemy->SetStrength(20);
	player->Heal(20);
	enemy->Heal(20);
	enemy->SetName("Bandit");
}

void Battle::MainLoop()
{
	char mainMenuChoice;
	setExtraInfo(&player, &enemy);
	printf("You have been waylaid by %s!\n", (enemy.GetName()).c_str());

	while (enemy.isAlive() && player.isAlive())
	{
		system("clear");
		MainBattleMenu();
		mainMenuChoice = GetMainMenuSelection();
		while(MainMenuSwitcher(mainMenuChoice) != TRUE)
		{
			mainMenuChoice = GetMainMenuSelection();
			printf("'%c' is not a valid option at this time. Choose something else.", mainMenuChoice);
		}

		playerMoves = playerMaxMoves;
		printf("Hit enter to proceed to the next turn...\n");
		getch();
		
	}
	
	//Battle over!
	if (enemy.IsAlive())
	{
		//player->Death();
	}
	printf("You have defeated %s!\n", (enemy.GetName()).c_str());
	printf("You gain %d xp.\n", enemy.GetXpBonus()); 

}


int main()
{
	PlayerCharacter player;
	EnemyHumanoid enemy;
	Battle battle(32, player, enemy);
	battle.MainLoop();
}


/*


////////////////////////////////////////////////
//FUNCTION NAME: Battle
//Input Parameters: character the character structure
//       enemy  the enemy structure
//variables: TotalType total Structure which holds the totals of the virtual dice rolls
//			 DamageType damage Structure which holds the damages of the various ways damage can be done
//			 Boolean melee_weapon=TRUE A boolean telling whether the character even has a melee weapon equipped
//			 Int8 battle_menu_choice User input: user selection from the battle menu, which determines what the character does
//	 		 Int8 distance	The number of yards between the character and opposition, divided by 6
//			 Int8 num_moves	 Number of moves the character has left
//			 Int8 enemy_moves  Number of moves the enemy has left
//			 Boolean sword_drawn Boolean telling whether the character's sword (if equipped) is drawn and able to be used
//			 Int16 arrow  Holds the number of arrows left (not permanant)
//			 Int16 character_run_attempt  Contains the number which will be opposed to enemy_run_attempt to see if the character successfully escaped
//			 Int16 enemy_run_attempt  Opposes the character run attempt to try to keep the character from escaping
//			 Byte yes_no  User-input character: Y or N; Yes or No
//			 char forward_backward user-input: does the user want to move fowards or backwards?
//
//Description: This highly complex function controls all battling for
//my RPG. As soon as a battle is entered, this function is called, and
//not exited till the end of the battle. It relies heavily on confusing
//variable manipulation.
void  Battle(CharacterType *character, EnemyType *enemy)
{
	TotalType total;
	DamageType damage;
	Boolean melee_weapon=TRUE;
	Int8 battle_menu_choice='0';
	Int8 distance=5;
	Int8 num_moves;
	Int8 enemy_moves=ENEMY_BATTLE_MOVES;
	Boolean sword_drawn=FALSE;
	Int16 arrow=TOTAL_ARROWS;
	Int16 character_run_attempt;
	Int16 enemy_run_attempt;
	char forward_backward;
	Byte yes_no;
		seedrnd();
		character->battle_run=FALSE; //Character so far has not run from the battle
		//Main body of the Battle function: runs while both the 
		//character and his opposition are still alive (have health
		//above zero).
		printf ("You encounter a %s!\n",enemy->enemy_name[enemy->enemy_number]);
		if (character->footWear==MOCCASINS)
			{
				sword_drawn=TRUE;
			}
		character->footWear=NO_FOOTWEAR;
		enemy->battle_run=FALSE;
		while (enemy->health>0 && character->health>0 && character->battle_run==FALSE && enemy->battle_run==FALSE)
			{
				if (battle_menu_choice=='6')
					{
						character->skill.defense--;
					}
				if (enemy->speed>character->attributes.agility_mod && enemy_moves==2)
					{
						num_moves=0;
					}
				else
					{
						num_moves=CHCTR_BATTLE_MOVES; //Character has two moves
					}
				//While character still has moves to spend, he can perform
				//the following actions....
				while (num_moves>0)
					{	
						if (character->righthand==LONG_SWORD || character->righthand==SHORT_SWORD || character->righthand==SCIMITAR || character->righthand==SABRE || character->righthand==KATANA || character->righthand==DAGGER || character->righthand==AX || character->righthand==MACE || character->righthand==LONGSWORD_PLUS_TWO || character->righthand==LONGSWORD_PLUS_ONE)
							{
								melee_weapon=TRUE; //Character has a melee weapon equipped
							}
						else
							{
								melee_weapon=FALSE; //Character does not have a melee weapon equipped
								sword_drawn=FALSE;
							}
						printf ("\nYou are %i yards from the %s.\n",distance*6, enemy->enemy_name[enemy->enemy_number]);
						printf ("Your options are:\n");
						////////////////////////////////////////
						/////The #1 options
						///////////////////////////////////////
						if (distance==0 && sword_drawn==TRUE)
							{
								printf ("1.Use %s\n",character->righthand_name[character->righthand]);
							}
						else if (distance==0 && sword_drawn==FALSE)
							{
								printf ("1.Punch\n");
							}
						else if (distance!=0 && character->righthand==ARROWS && arrow>0)
							{
								printf ("1.Fire Arrows\n");
							}
						else 
							{
								printf ("1.Pray\n");
							}
						////////////////////////////////////////
						/////The #2 options
						///////////////////////////////////////
						if (distance==0 && sword_drawn==TRUE && num_moves==2)
							{
								printf("2.Two-Handed Melee Attack\n");
							}
						else if (distance==0 && sword_drawn==FALSE && num_moves==2)
							{
								printf ("2.Charge\n");
							}
						else if (distance!=0 && character->righthand==DAGGER)
							{
								printf ("2.Throw Knife\n");
							}
						else 
							{
								printf ("2.Do Nothing\n");
							}
						////////////////////////////////////////
						/////The #3 options
						///////////////////////////////////////
						if (distance==0)
							{
								printf("3.Back Away\n");
							}
						else
							{
								printf ("3.Move Forward Or Back Away\n");
							}
						////////////////////////////////////////
						/////The #4 options
						///////////////////////////////////////
						if (sword_drawn==TRUE && melee_weapon==TRUE)
							{
								printf ("4.Put Away Melee Weapon\n");
							}
						else if (sword_drawn==FALSE && melee_weapon==TRUE)
							{
								printf ("4.Draw Melee Weapon\n");
							}
						else
							{
								printf ("4.Don't do a thing\n");
							}
						////////////////////////////////////////
						/////The remaining options
						///////////////////////////////////////
						printf ("5.Run From Battle\n");
						printf ("6.Stand Your Ground\n");
						if (character->righthand==NO_ITEM)
							{
								printf ("7.Equip weapon\n");
							}
						else
							{
								printf ("7.Switch equipped weapon\n");
							}
						printf ("8. Use Spell\n");
						printf ("Which do you choose?\n");
						battle_menu_choice=getch();
						////////////////////////////////////////
						/////User selected #1 
						///////////////////////////////////////
						if(battle_menu_choice=='1')
							{
								dice_rolls(character,enemy,&total,&damage);
								if (distance==0 && sword_drawn==TRUE)
									{
										num_moves--; //Uses 1 move
										//Regular attack
										printf ("You swing at the %s with your %s!\n",enemy->enemy_name[enemy->enemy_number],character->righthand_name[character->righthand]);
										total.eleven=total.ten+character->skill.melee_attack;
										//If the characters attack is greater than enemy defense 
										if (total.eleven>=enemy->defense && damage.sword_damage+character->skill.melee_weapon_bonus[character->righthand]>=enemy->armor)
											{
												printf ("You hit!\n");
												//Takes away damage amount from the enemies health
												enemy->health-=damage.sword_damage+enemy->armor+character->skill.melee_weapon_bonus[character->righthand];
											}
										else
											{
												printf ("You missed!\n");
											}
									}
								else if (distance==0 && sword_drawn==FALSE)
									{
										num_moves--;
										//Physical attack; punch
										printf ("You punched the %s!\n",enemy->enemy_name[enemy->enemy_number]);
										total.eleven=total.ten+character->skill.melee_attack;
										if (total.eleven>enemy->defense && damage.punch_damage>=enemy->armor)
											{
												printf ("You hit!\n");
												enemy->health-=damage.punch_damage-enemy->armor; 
											}
										else
											{
												printf ("You missed!\n");
											}	
									}
								else if (distance!=0 && character->righthand==ARROWS && arrow>0)
									{
										//Ranged weapon; Arrows
										num_moves--;
										printf ("You used your %s against the %s!!\n",character->righthand_name[character->righthand], enemy->enemy_name[enemy->enemy_number]);
										arrow--;
										if (arrow<1)
											{
												printf ("You just used your last arrow!\n");
											}
										//Accuracy reduction for distance from enemy
										if (distance<=1)
											{
												total.eleven=total.ten+character->skill.melee_attack;
											}
										else if (distance>1 && distance<=5)
											{
												total.eleven=total.ten+character->skill.melee_attack-1;
											}
										else if (distance>5)
											{
												total.eleven=total.ten+character->skill.melee_attack-2;
											}
										//Determine if character hit
										if (total.eleven>enemy->defense && damage.ranged_damage>=enemy->armor)
											{
												printf ("You hit!\n");
												enemy->health-=damage.ranged_damage-enemy->armor+character->skill.ranged_weapon_bonus[character->righthand];
											}
										else
											{
												printf ("You missed!\n");
											}

									}
								else 
									{
										num_moves--;
										printf ("You fall to the ground and pray to the Lord.\nEither that, or your deceased father...\n");	
									}
							}
						////////////////////////////////////////
						/////User selected #2 
						///////////////////////////////////////
						else if(battle_menu_choice=='2')
							{
								if (num_moves==2)
									{
										dice_rolls(character,enemy,&total,&damage);
										character->skill.defense=character->skill.defense-3;
										num_moves=num_moves-2; //Selection #2 takes 2 moves
										if (distance==0 && sword_drawn==TRUE)
											{
												//Two-handed attack
												printf ("You performed a two-handed melee attack against the %s!\n",enemy->enemy_name[enemy->enemy_number]);
												total.eleven=total.ten+character->skill.melee_attack;
												if (total.eleven>enemy->defense && damage.two_handed_attack_damage>=enemy->armor)
													{
														printf ("You hit!\n");
														enemy->health-=damage.two_handed_attack_damage-enemy->armor;
													}
												else
													{
														printf ("You missed!\n");
													}
											}
										else if (distance==0 && sword_drawn==FALSE)
											{
												//Unarmed charge
												printf ("You charged the %s!\n",enemy->enemy_name[enemy->enemy_number]);
												total.eleven=total.ten+character->skill.melee_attack;
												if (total.eleven>enemy->defense && damage.charge_damage>=enemy->armor)
													{
														printf ("You hit!\n");
														enemy->health-=damage.charge_damage-enemy->armor;
													}
												else
													{
														printf ("You missed!\n");
													}
											}
										else if (distance!=0 && character->righthand==DAGGER)
											{
												//Throw Dagger
												character->skill.defense=character->skill.defense+3;
												printf ("You threw a knife at the %s!!\n",enemy->enemy_name[enemy->enemy_number]);
												//Reduce accuracy and chance of striking enemy
												//for distance from enemy
												if (distance<=1)
													{
														total.eleven=total.ten+character->skill.melee_attack;
													}
												else if (distance>1 && distance<=5)
													{
														total.eleven=total.ten+character->skill.melee_attack-1;
													}
												else if (distance>5)
													{
														total.eleven=total.ten+character->skill.melee_attack-2;
													}
											     //Check if the knife hit
											     if (total.eleven>enemy->defense && damage.knife_damage>=enemy->armor)
													{
														printf ("You hit!\n");
														enemy->health-=damage.knife_damage-enemy->armor;
													}
												else
													{
														printf ("You missed!\n");
													}
											}
										else 
											{
												//Do nothing
												printf ("You are doing nothing, when you remember that idleness is wastefulness.\n");
											}
									}
								else
									{
										num_moves=num_moves-1; //This only takes 1 move
										//Do nothing
										printf ("You are doing nothing, when you remember that idleness is wastefulness.\n");
									}
							}
						////////////////////////////////////////
						/////User selected #3
						/////Move forward or backwards 
						///////////////////////////////////////
						else if(battle_menu_choice=='3')
							{
								num_moves--; //This move takes 1 move
								if(distance==0)
									{
										distance++; //Move backwards
									}
								else
									{
										printf ("(F)orwards or (B)ackwards?\n");
										forward_backward=toupper(getch());
										if (forward_backward=='F')
											{
												distance--; //Move forwards
											}
										else if (forward_backward=='B')
											{
												distance++;	//Move backwards
											}
										else
											{
												num_moves++; //give the move back to user
												printf ("ERROR:ILLEGAL COMMAND!");
											}
									}
							}
						///////////////////////////////////////////
						/////User selected #4
						/////Draw or sheath equipped melee weapon 
						///////////////////////////////////////////
						else if(battle_menu_choice=='4')
							{
								num_moves--; //Takes 1 move
								if (sword_drawn==TRUE) //If sword is drawn
									{
										sword_drawn=FALSE; //Sheath sword
									}
								else if (sword_drawn==FALSE && melee_weapon==TRUE)//If sword is sheathed
									{
										sword_drawn=TRUE; //Draw sword
									}
								else
									{
										//Do nothing
										printf ("You stand there looking stupid!!");
									}
							}
						////////////////////////////////////////
						/////User selected #5 
						/////Run from battle
						///////////////////////////////////////
						else if(battle_menu_choice=='5')
							{
								if (enemy->enemy_number<NUM_OF_ENEMIES)
									{
										num_moves=num_moves-2; //Takes both moves
										dice_rolls(character,enemy,&total,&damage);
										printf ("You attempt to run...");
										character_run_attempt=total.ten+character->attributes.agility_mod;
										enemy_run_attempt=total.nine+enemy->speed;
										//Compare the character's run attempt with
										//the enemies roll and speed, and see which
										//is greater
										if (enemy_run_attempt<=character_run_attempt)
											{
												//You ran away
												character->battle_run=TRUE;
											}
										if (enemy_run_attempt>character_run_attempt)
											{
												//He didn't escape
												printf ("You failed to escape.\n");
											}
									}
								else 
									{
										printf ("You can't run from such an important battle!\n");
									}
							}
						////////////////////////////////////////
						/////User selected #6
						/////Stand your guard, fortify position 
						///////////////////////////////////////
						else if(battle_menu_choice=='6')
							{
								num_moves-=2; //Takes two moves
								character->skill.defense++; //Increment defense; guard
							}
						////////////////////////////////////////
						/////User selected #7
						/////Switch Equipped Weapons
						///////////////////////////////////////
						else if (battle_menu_choice=='7')
							{
								weapon_switch(character);
							}
						////////////////////////////////////////
						/////User selected #8
						/////Use Magic Spells
						///////////////////////////////////////
						else if (battle_menu_choice=='8')
							{
								if ((character->magic_attributes.spellpoints-character->magic_attributes.spellpoints_required[character->magic_attributes.equipped_spell])<=0)
									{
										printf ("Not enough spellpoints!\n");
									}
								else 
									{
										dice_rolls(character,enemy,&total,&damage);
										printf ("You used the spell %s!\n",character->magic_attributes.spell_name[character->magic_attributes.equipped_spell]);
										use_spell(character,enemy,&total);
										enemy->health-=character->magic_attributes.spell_damage;
										printf ("It did %i damage!\n",character->magic_attributes.spell_damage);
									}
							}
						//////////////////////////////////////
						//////Illegal Selection
						/////////////////////////////////////
						else if(battle_menu_choice<'1' || battle_menu_choice>'7')
							{
								printf ("ERROR: User-input value was not one of the options!\n");
							}
						if (enemy->health<=0)
							{
								num_moves=0;
							}
					}
				///////////////////////////////////////////
				////////////THE ENEMY'S TURN
				//This is essentially a copy of the characters
				//options, only the computer makes the 
				//decision of what move to use.
				//////////////////////////////////////////
				if (enemy->health>0 && character->battle_run==FALSE)
					{	
						enemy_moves=ENEMY_BATTLE_MOVES; //The enemy also has two moves
						while (enemy_moves>0)
							{	
								dice_rolls(character,enemy,&total,&damage);
								if (distance==0)
									{
										enemy_moves--;
										if (enemy->health>13 || character->health<16)
											{
												printf ("\nThe %s makes a melee attack against you\n",enemy->enemy_name[enemy->enemy_number]);
												total.eleven=total.twelve+enemy->melee_attack;
												if(total.eleven>character->skill.defense)
													{
														printf ("He hit!\n");
														character->health-=total.twelve+enemy->melee_damage_bonus-character->armorbonus;
													}
												else
													{
														printf ("He missed!\n");
													}
											}
										else
											{
												printf ("The %s moved away from you!\n",enemy->enemy_name[enemy->enemy_number]);
												distance++;
											}
									}
								else if (distance!=0)
									{
										enemy_moves--;
										if (enemy->health*3.5<character->health)
											{
												enemy_moves-=2; //Takes both moves
												dice_rolls(character,enemy,&total,&damage);
												printf ("The enemy attempts to run...");
												character_run_attempt=total.ten+character->attributes.agility_mod;
												enemy_run_attempt=total.nine+enemy->speed;
												//Compare the character's run attempt with
												//the enemies roll and speed, and see which
												//is greater
												if (enemy_run_attempt<=character_run_attempt)
													{
														printf ("He failed to escape.\n");
													}
												if (enemy_run_attempt>character_run_attempt)
													{
														enemy->battle_run=TRUE;	
													}
											}	
										else if (enemy->health<character->health*2 && enemy->ranged_attack!=0 || character->skill.melee_attack>character->skill.ranged_attack && enemy->ranged_attack!=0)
											{
												printf ("\nThe %s uses its ranged attack!\n",enemy->enemy_name[enemy->enemy_number]);
												total.eleven=total.twelve+enemy->ranged_attack;
												if(total.eleven>character->skill.defense)
													{
														printf ("He hit!\n");
														character->health-=total.twelve+enemy->melee_damage_bonus-character->armorbonus;
													}
												else
													{
														printf ("He missed!\n");
													}
											}
										else
											{
												printf ("\nThe %s moves toward you!\n",enemy->enemy_name[enemy->enemy_number]);
												distance--;
											}
									}
							}
					}
				//Display health
				if (character->health>0 && enemy->health>0 && character->battle_run==FALSE && enemy->battle_run==FALSE)
					{
						printf ("Health statistics are:\nYou: %i\n%s: %i\n",character->health,enemy->enemy_name[enemy->enemy_number],enemy->health);
					}		
			}
		//WHILE LOOP EXITED
		//If the character is the one with health over zero...
		if(enemy->health<1)
			{
				printf ("YOU WIN!\n");
				printf ("Gained %i experience\n",enemy->xp_bonus);
				enemy->enemy_won=FALSE; //The enemy did not win
				character->xp+=enemy->xp_bonus; //Give the character xp for beating the enemy
			}
		//If he is not.......
		else if(character->health<1)
			{
				enemy->enemy_won=TRUE; //The enemy won
				printf ("The world fades around you...Would you like to keep going?\n If you do, your xp will be reset. Y/N\n");
				yes_no=toupper(getch());
				switch(yes_no)
					{
						case 'Y':
							character->xp=0; //Set xp to zero; game restarted
							//Reset character's health to normal
							character->health=(character->attributes.constitution+character->attributes.strength_mod)*5;
						break;
						default:
							exit(1); //Quit game
						break;
					}
			}
		else if (character->battle_run==TRUE)
			{
				printf ("You successfully ran away!\n");
			}
		else if (enemy->battle_run==TRUE)
			{
				printf ("The enemy successfully ran away!\n");
				printf ("YOU WIN!\n");
				printf ("Gained %i experience\n",enemy->xp_bonus);
				enemy->enemy_won=FALSE; //The enemy did not win
				character->xp+=enemy->xp_bonus; //Give the character xp for beating the enemy
			}
}
*/
