#include "util_sdk.h"
#include "../interfaces.h"

#include <sstream>
#include <algorithm>

static const char *ActivityStrings[] =
{
	"ACT_RESET",
	"ACT_IDLE",
	"ACT_TRANSITION",
	"ACT_COVER",
	"ACT_COVER_MED",
	"ACT_COVER_LOW",
	"ACT_WALK",
	"ACT_WALK_AIM",
	"ACT_WALK_CROUCH",
	"ACT_WALK_CROUCH_AIM",
	"ACT_RUN",
	"ACT_RUN_AIM",
	"ACT_RUN_CROUCH",
	"ACT_RUN_CROUCH_AIM",
	"ACT_RUN_PROTECTED",
	"ACT_SCRIPT_CUSTOM_MOVE",
	"ACT_RANGE_ATTACK1",
	"ACT_RANGE_ATTACK2",
	"ACT_RANGE_ATTACK1_LOW",
	"ACT_RANGE_ATTACK2_LOW",
	"ACT_DIESIMPLE",
	"ACT_DIEBACKWARD",
	"ACT_DIEFORWARD",
	"ACT_DIEVIOLENT",
	"ACT_DIERAGDOLL",
	"ACT_FLY",
	"ACT_HOVER",
	"ACT_GLIDE",
	"ACT_SWIM",
	"ACT_JUMP",
	"ACT_HOP",
	"ACT_LEAP",
	"ACT_LAND",
	"ACT_CLIMB_UP",
	"ACT_CLIMB_DOWN",
	"ACT_CLIMB_DISMOUNT",
	"ACT_SHIPLADDER_UP",
	"ACT_SHIPLADDER_DOWN",
	"ACT_STRAFE_LEFT",
	"ACT_STRAFE_RIGHT",
	"ACT_ROLL_LEFT",
	"ACT_ROLL_RIGHT",
	"ACT_TURN_LEFT",
	"ACT_TURN_RIGHT",
	"ACT_CROUCH",
	"ACT_CROUCHIDLE",
	"ACT_STAND",
	"ACT_USE",
	"ACT_ALIEN_BURROW_IDLE",
	"ACT_ALIEN_BURROW_OUT",
	"ACT_SIGNAL1",
	"ACT_SIGNAL2",
	"ACT_SIGNAL3",
	"ACT_SIGNAL_ADVANCE",
	"ACT_SIGNAL_FORWARD",
	"ACT_SIGNAL_GROUP",
	"ACT_SIGNAL_HALT",
	"ACT_SIGNAL_LEFT",
	"ACT_SIGNAL_RIGHT",
	"ACT_SIGNAL_TAKECOVER",
	"ACT_LOOKBACK_RIGHT",
	"ACT_LOOKBACK_LEFT",
	"ACT_COWER",
	"ACT_SMALL_FLINCH",
	"ACT_BIG_FLINCH",
	"ACT_MELEE_ATTACK1",
	"ACT_MELEE_ATTACK2",
	"ACT_RELOAD",
	"ACT_RELOAD_START",
	"ACT_RELOAD_FINISH",
	"ACT_RELOAD_LOW",
	"ACT_ARM",
	"ACT_DISARM",
	"ACT_DROP_WEAPON",
	"ACT_DROP_WEAPON_SHOTGUN",
	"ACT_PICKUP_GROUND",
	"ACT_PICKUP_RACK",
	"ACT_IDLE_ANGRY",
	"ACT_IDLE_RELAXED",
	"ACT_IDLE_STIMULATED",
	"ACT_IDLE_AGITATED",
	"ACT_IDLE_STEALTH",
	"ACT_IDLE_HURT",
	"ACT_WALK_RELAXED",
	"ACT_WALK_STIMULATED",
	"ACT_WALK_AGITATED",
	"ACT_WALK_STEALTH",
	"ACT_RUN_RELAXED",
	"ACT_RUN_STIMULATED",
	"ACT_RUN_AGITATED",
	"ACT_RUN_STEALTH",
	"ACT_IDLE_AIM_RELAXED",
	"ACT_IDLE_AIM_STIMULATED",
	"ACT_IDLE_AIM_AGITATED",
	"ACT_IDLE_AIM_STEALTH",
	"ACT_WALK_AIM_RELAXED",
	"ACT_WALK_AIM_STIMULATED",
	"ACT_WALK_AIM_AGITATED",
	"ACT_WALK_AIM_STEALTH",
	"ACT_RUN_AIM_RELAXED",
	"ACT_RUN_AIM_STIMULATED",
	"ACT_RUN_AIM_AGITATED",
	"ACT_RUN_AIM_STEALTH",
	"ACT_CROUCHIDLE_STIMULATED",
	"ACT_CROUCHIDLE_AIM_STIMULATED",
	"ACT_CROUCHIDLE_AGITATED",
	"ACT_WALK_HURT",
	"ACT_RUN_HURT",
	"ACT_SPECIAL_ATTACK1",
	"ACT_SPECIAL_ATTACK2",
	"ACT_COMBAT_IDLE",
	"ACT_WALK_SCARED",
	"ACT_RUN_SCARED",
	"ACT_VICTORY_DANCE",
	"ACT_DIE_HEADSHOT",
	"ACT_DIE_CHESTSHOT",
	"ACT_DIE_GUTSHOT",
	"ACT_DIE_BACKSHOT",
	"ACT_FLINCH_HEAD",
	"ACT_FLINCH_CHEST",
	"ACT_FLINCH_STOMACH",
	"ACT_FLINCH_LEFTARM",
	"ACT_FLINCH_RIGHTARM",
	"ACT_FLINCH_LEFTLEG",
	"ACT_FLINCH_RIGHTLEG",
	"ACT_FLINCH_PHYSICS",
	"ACT_FLINCH_HEAD_BACK",
	"ACT_FLINCH_HEAD_LEFT",
	"ACT_FLINCH_HEAD_RIGHT",
	"ACT_FLINCH_CHEST_BACK",
	"ACT_FLINCH_STOMACH_BACK",
	"ACT_FLINCH_CROUCH_FRONT",
	"ACT_FLINCH_CROUCH_BACK",
	"ACT_FLINCH_CROUCH_LEFT",
	"ACT_FLINCH_CROUCH_RIGHT",
	"ACT_IDLE_ON_FIRE",
	"ACT_WALK_ON_FIRE",
	"ACT_RUN_ON_FIRE",
	"ACT_RAPPEL_LOOP",
	"ACT_180_LEFT",
	"ACT_180_RIGHT",
	"ACT_90_LEFT",
	"ACT_90_RIGHT",
	"ACT_STEP_LEFT",
	"ACT_STEP_RIGHT",
	"ACT_STEP_BACK",
	"ACT_STEP_FORE",
	"ACT_GESTURE_RANGE_ATTACK1",
	"ACT_GESTURE_RANGE_ATTACK2",
	"ACT_GESTURE_MELEE_ATTACK1",
	"ACT_GESTURE_MELEE_ATTACK2",
	"ACT_GESTURE_RANGE_ATTACK1_LOW",
	"ACT_GESTURE_RANGE_ATTACK2_LOW",
	"ACT_MELEE_ATTACK_SWING_GESTURE",
	"ACT_GESTURE_SMALL_FLINCH",
	"ACT_GESTURE_BIG_FLINCH",
	"ACT_GESTURE_FLINCH_BLAST",
	"ACT_GESTURE_FLINCH_BLAST_SHOTGUN",
	"ACT_GESTURE_FLINCH_BLAST_DAMAGED",
	"ACT_GESTURE_FLINCH_BLAST_DAMAGED_SHOTGUN",
	"ACT_GESTURE_FLINCH_HEAD",
	"ACT_GESTURE_FLINCH_CHEST",
	"ACT_GESTURE_FLINCH_STOMACH",
	"ACT_GESTURE_FLINCH_LEFTARM",
	"ACT_GESTURE_FLINCH_RIGHTARM",
	"ACT_GESTURE_FLINCH_LEFTLEG",
	"ACT_GESTURE_FLINCH_RIGHTLEG",
	"ACT_GESTURE_TURN_LEFT",
	"ACT_GESTURE_TURN_RIGHT",
	"ACT_GESTURE_TURN_LEFT45",
	"ACT_GESTURE_TURN_RIGHT45",
	"ACT_GESTURE_TURN_LEFT90",
	"ACT_GESTURE_TURN_RIGHT90",
	"ACT_GESTURE_TURN_LEFT45_FLAT",
	"ACT_GESTURE_TURN_RIGHT45_FLAT",
	"ACT_GESTURE_TURN_LEFT90_FLAT",
	"ACT_GESTURE_TURN_RIGHT90_FLAT",
	"ACT_BARNACLE_HIT",
	"ACT_BARNACLE_PULL",
	"ACT_BARNACLE_CHOMP",
	"ACT_BARNACLE_CHEW",
	"ACT_DO_NOT_DISTURB",
	"ACT_SPECIFIC_SEQUENCE",
	"ACT_VM_DRAW",
	"ACT_VM_HOLSTER",
	"ACT_VM_IDLE",
	"ACT_VM_FIDGET",
	"ACT_VM_PULLBACK",
	"ACT_VM_PULLBACK_HIGH",
	"ACT_VM_PULLBACK_LOW",
	"ACT_VM_THROW",
	"ACT_VM_PULLPIN",
	"ACT_VM_PRIMARYATTACK",
	"ACT_VM_SECONDARYATTACK",
	"ACT_VM_RELOAD",
	"ACT_VM_DRYFIRE",
	"ACT_VM_HITLEFT",
	"ACT_VM_HITLEFT2",
	"ACT_VM_HITRIGHT",
	"ACT_VM_HITRIGHT2",
	"ACT_VM_HITCENTER",
	"ACT_VM_HITCENTER2",
	"ACT_VM_MISSLEFT",
	"ACT_VM_MISSLEFT2",
	"ACT_VM_MISSRIGHT",
	"ACT_VM_MISSRIGHT2",
	"ACT_VM_MISSCENTER",
	"ACT_VM_MISSCENTER2",
	"ACT_VM_HAULBACK",
	"ACT_VM_SWINGHARD",
	"ACT_VM_SWINGMISS",
	"ACT_VM_SWINGHIT",
	"ACT_VM_IDLE_TO_LOWERED",
	"ACT_VM_IDLE_LOWERED",
	"ACT_VM_LOWERED_TO_IDLE",
	"ACT_VM_RECOIL1",
	"ACT_VM_RECOIL2",
	"ACT_VM_RECOIL3",
	"ACT_VM_PICKUP",
	"ACT_VM_RELEASE",
	"ACT_VM_ATTACH_SILENCER",
	"ACT_VM_DETACH_SILENCER",
	"ACT_VM_EMPTY_FIRE",
	"ACT_VM_EMPTY_RELOAD",
	"ACT_VM_EMPTY_DRAW",
	"ACT_VM_EMPTY_IDLE",
	"ACT_SLAM_STICKWALL_IDLE",
	"ACT_SLAM_STICKWALL_ND_IDLE",
	"ACT_SLAM_STICKWALL_ATTACH",
	"ACT_SLAM_STICKWALL_ATTACH2",
	"ACT_SLAM_STICKWALL_ND_ATTACH",
	"ACT_SLAM_STICKWALL_ND_ATTACH2",
	"ACT_SLAM_STICKWALL_DETONATE",
	"ACT_SLAM_STICKWALL_DETONATOR_HOLSTER",
	"ACT_SLAM_STICKWALL_DRAW",
	"ACT_SLAM_STICKWALL_ND_DRAW",
	"ACT_SLAM_STICKWALL_TO_THROW",
	"ACT_SLAM_STICKWALL_TO_THROW_ND",
	"ACT_SLAM_STICKWALL_TO_TRIPMINE_ND",
	"ACT_SLAM_THROW_IDLE",
	"ACT_SLAM_THROW_ND_IDLE",
	"ACT_SLAM_THROW_THROW",
	"ACT_SLAM_THROW_THROW2",
	"ACT_SLAM_THROW_THROW_ND",
	"ACT_SLAM_THROW_THROW_ND2",
	"ACT_SLAM_THROW_DRAW",
	"ACT_SLAM_THROW_ND_DRAW",
	"ACT_SLAM_THROW_TO_STICKWALL",
	"ACT_SLAM_THROW_TO_STICKWALL_ND",
	"ACT_SLAM_THROW_DETONATE",
	"ACT_SLAM_THROW_DETONATOR_HOLSTER",
	"ACT_SLAM_THROW_TO_TRIPMINE_ND",
	"ACT_SLAM_TRIPMINE_IDLE",
	"ACT_SLAM_TRIPMINE_DRAW",
	"ACT_SLAM_TRIPMINE_ATTACH",
	"ACT_SLAM_TRIPMINE_ATTACH2",
	"ACT_SLAM_TRIPMINE_TO_STICKWALL_ND",
	"ACT_SLAM_TRIPMINE_TO_THROW_ND",
	"ACT_SLAM_DETONATOR_IDLE",
	"ACT_SLAM_DETONATOR_DRAW",
	"ACT_SLAM_DETONATOR_DETONATE",
	"ACT_SLAM_DETONATOR_HOLSTER",
	"ACT_SLAM_DETONATOR_STICKWALL_DRAW",
	"ACT_SLAM_DETONATOR_THROW_DRAW",
	"ACT_SHOTGUN_RELOAD_START",
	"ACT_SHOTGUN_RELOAD_FINISH",
	"ACT_SHOTGUN_PUMP",
	"ACT_SMG2_IDLE2",
	"ACT_SMG2_FIRE2",
	"ACT_SMG2_DRAW2",
	"ACT_SMG2_RELOAD2",
	"ACT_SMG2_DRYFIRE2",
	"ACT_SMG2_TOAUTO",
	"ACT_SMG2_TOBURST",
	"ACT_PHYSCANNON_UPGRADE",
	"ACT_RANGE_ATTACK_AR1",
	"ACT_RANGE_ATTACK_AR2",
	"ACT_RANGE_ATTACK_AR2_LOW",
	"ACT_RANGE_ATTACK_AR2_GRENADE",
	"ACT_RANGE_ATTACK_HMG1",
	"ACT_RANGE_ATTACK_ML",
	"ACT_RANGE_ATTACK_SMG1",
	"ACT_RANGE_ATTACK_SMG1_LOW",
	"ACT_RANGE_ATTACK_SMG2",
	"ACT_RANGE_ATTACK_SHOTGUN",
	"ACT_RANGE_ATTACK_SHOTGUN_LOW",
	"ACT_RANGE_ATTACK_PISTOL",
	"ACT_RANGE_ATTACK_PISTOL_LOW",
	"ACT_RANGE_ATTACK_SLAM",
	"ACT_RANGE_ATTACK_TRIPWIRE",
	"ACT_RANGE_ATTACK_THROW",
	"ACT_RANGE_ATTACK_SNIPER_RIFLE",
	"ACT_RANGE_ATTACK_RPG",
	"ACT_MELEE_ATTACK_SWING",
	"ACT_RANGE_AIM_LOW",
	"ACT_RANGE_AIM_SMG1_LOW",
	"ACT_RANGE_AIM_PISTOL_LOW",
	"ACT_RANGE_AIM_AR2_LOW",
	"ACT_COVER_PISTOL_LOW",
	"ACT_COVER_SMG1_LOW",
	"ACT_GESTURE_RANGE_ATTACK_AR1",
	"ACT_GESTURE_RANGE_ATTACK_AR2",
	"ACT_GESTURE_RANGE_ATTACK_AR2_GRENADE",
	"ACT_GESTURE_RANGE_ATTACK_HMG1",
	"ACT_GESTURE_RANGE_ATTACK_ML",
	"ACT_GESTURE_RANGE_ATTACK_SMG1",
	"ACT_GESTURE_RANGE_ATTACK_SMG1_LOW",
	"ACT_GESTURE_RANGE_ATTACK_SMG2",
	"ACT_GESTURE_RANGE_ATTACK_SHOTGUN",
	"ACT_GESTURE_RANGE_ATTACK_PISTOL",
	"ACT_GESTURE_RANGE_ATTACK_PISTOL_LOW",
	"ACT_GESTURE_RANGE_ATTACK_SLAM",
	"ACT_GESTURE_RANGE_ATTACK_TRIPWIRE",
	"ACT_GESTURE_RANGE_ATTACK_THROW",
	"ACT_GESTURE_RANGE_ATTACK_SNIPER_RIFLE",
	"ACT_GESTURE_MELEE_ATTACK_SWING",
	"ACT_IDLE_RIFLE",
	"ACT_IDLE_SMG1",
	"ACT_IDLE_ANGRY_SMG1",
	"ACT_IDLE_PISTOL",
	"ACT_IDLE_ANGRY_PISTOL",
	"ACT_IDLE_ANGRY_SHOTGUN",
	"ACT_IDLE_STEALTH_PISTOL",
	"ACT_IDLE_PACKAGE",
	"ACT_WALK_PACKAGE",
	"ACT_IDLE_SUITCASE",
	"ACT_WALK_SUITCASE",
	"ACT_IDLE_SMG1_RELAXED",
	"ACT_IDLE_SMG1_STIMULATED",
	"ACT_WALK_RIFLE_RELAXED",
	"ACT_RUN_RIFLE_RELAXED",
	"ACT_WALK_RIFLE_STIMULATED",
	"ACT_RUN_RIFLE_STIMULATED",
	"ACT_IDLE_AIM_RIFLE_STIMULATED",
	"ACT_WALK_AIM_RIFLE_STIMULATED",
	"ACT_RUN_AIM_RIFLE_STIMULATED",
	"ACT_IDLE_SHOTGUN_RELAXED",
	"ACT_IDLE_SHOTGUN_STIMULATED",
	"ACT_IDLE_SHOTGUN_AGITATED",
	"ACT_WALK_ANGRY",
	"ACT_POLICE_HARASS1",
	"ACT_POLICE_HARASS2",
	"ACT_IDLE_MANNEDGUN",
	"ACT_IDLE_MELEE",
	"ACT_IDLE_ANGRY_MELEE",
	"ACT_IDLE_RPG_RELAXED",
	"ACT_IDLE_RPG",
	"ACT_IDLE_ANGRY_RPG",
	"ACT_COVER_LOW_RPG",
	"ACT_WALK_RPG",
	"ACT_RUN_RPG",
	"ACT_WALK_CROUCH_RPG",
	"ACT_RUN_CROUCH_RPG",
	"ACT_WALK_RPG_RELAXED",
	"ACT_RUN_RPG_RELAXED",
	"ACT_WALK_RIFLE",
	"ACT_WALK_AIM_RIFLE",
	"ACT_WALK_CROUCH_RIFLE",
	"ACT_WALK_CROUCH_AIM_RIFLE",
	"ACT_RUN_RIFLE",
	"ACT_RUN_AIM_RIFLE",
	"ACT_RUN_CROUCH_RIFLE",
	"ACT_RUN_CROUCH_AIM_RIFLE",
	"ACT_RUN_STEALTH_PISTOL",
	"ACT_WALK_AIM_SHOTGUN",
	"ACT_RUN_AIM_SHOTGUN",
	"ACT_WALK_PISTOL",
	"ACT_RUN_PISTOL",
	"ACT_WALK_AIM_PISTOL",
	"ACT_RUN_AIM_PISTOL",
	"ACT_WALK_STEALTH_PISTOL",
	"ACT_WALK_AIM_STEALTH_PISTOL",
	"ACT_RUN_AIM_STEALTH_PISTOL",
	"ACT_RELOAD_PISTOL",
	"ACT_RELOAD_PISTOL_LOW",
	"ACT_RELOAD_SMG1",
	"ACT_RELOAD_SMG1_LOW",
	"ACT_RELOAD_SHOTGUN",
	"ACT_RELOAD_SHOTGUN_LOW",
	"ACT_GESTURE_RELOAD",
	"ACT_GESTURE_RELOAD_PISTOL",
	"ACT_GESTURE_RELOAD_SMG1",
	"ACT_GESTURE_RELOAD_SHOTGUN",
	"ACT_BUSY_LEAN_LEFT",
	"ACT_BUSY_LEAN_LEFT_ENTRY",
	"ACT_BUSY_LEAN_LEFT_EXIT",
	"ACT_BUSY_LEAN_BACK",
	"ACT_BUSY_LEAN_BACK_ENTRY",
	"ACT_BUSY_LEAN_BACK_EXIT",
	"ACT_BUSY_SIT_GROUND",
	"ACT_BUSY_SIT_GROUND_ENTRY",
	"ACT_BUSY_SIT_GROUND_EXIT",
	"ACT_BUSY_SIT_CHAIR",
	"ACT_BUSY_SIT_CHAIR_ENTRY",
	"ACT_BUSY_SIT_CHAIR_EXIT",
	"ACT_BUSY_STAND",
	"ACT_BUSY_QUEUE",
	"ACT_DUCK_DODGE",
	"ACT_DIE_BARNACLE_SWALLOW",
	"ACT_GESTURE_BARNACLE_STRANGLE",
	"ACT_PHYSCANNON_DETACH",
	"ACT_PHYSCANNON_ANIMATE",
	"ACT_PHYSCANNON_ANIMATE_PRE",
	"ACT_PHYSCANNON_ANIMATE_POST",
	"ACT_DIE_FRONTSIDE",
	"ACT_DIE_RIGHTSIDE",
	"ACT_DIE_BACKSIDE",
	"ACT_DIE_LEFTSIDE",
	"ACT_DIE_CROUCH_FRONTSIDE",
	"ACT_DIE_CROUCH_RIGHTSIDE",
	"ACT_DIE_CROUCH_BACKSIDE",
	"ACT_DIE_CROUCH_LEFTSIDE",
	"ACT_OPEN_DOOR",
	"ACT_DI_ALYX_ZOMBIE_MELEE",
	"ACT_DI_ALYX_ZOMBIE_TORSO_MELEE",
	"ACT_DI_ALYX_HEADCRAB_MELEE",
	"ACT_DI_ALYX_ANTLION",
	"ACT_DI_ALYX_ZOMBIE_SHOTGUN64",
	"ACT_DI_ALYX_ZOMBIE_SHOTGUN26",
	"ACT_READINESS_RELAXED_TO_STIMULATED",
	"ACT_READINESS_RELAXED_TO_STIMULATED_WALK",
	"ACT_READINESS_AGITATED_TO_STIMULATED",
	"ACT_READINESS_STIMULATED_TO_RELAXED",
	"ACT_READINESS_PISTOL_RELAXED_TO_STIMULATED",
	"ACT_READINESS_PISTOL_RELAXED_TO_STIMULATED_WALK",
	"ACT_READINESS_PISTOL_AGITATED_TO_STIMULATED",
	"ACT_READINESS_PISTOL_STIMULATED_TO_RELAXED",
	"ACT_IDLE_CARRY",
	"ACT_WALK_CARRY",
	"ACT_STARTDYING",
	"ACT_DYINGLOOP",
	"ACT_DYINGTODEAD",
	"ACT_RIDE_MANNED_GUN",
	"ACT_VM_SPRINT_ENTER",
	"ACT_VM_SPRINT_IDLE",
	"ACT_VM_SPRINT_LEAVE",
	"ACT_FIRE_START",
	"ACT_FIRE_LOOP",
	"ACT_FIRE_END",
	"ACT_CROUCHING_GRENADEIDLE",
	"ACT_CROUCHING_GRENADEREADY",
	"ACT_CROUCHING_PRIMARYATTACK",
	"ACT_OVERLAY_GRENADEIDLE",
	"ACT_OVERLAY_GRENADEREADY",
	"ACT_OVERLAY_PRIMARYATTACK",
	"ACT_OVERLAY_SHIELD_UP",
	"ACT_OVERLAY_SHIELD_DOWN",
	"ACT_OVERLAY_SHIELD_UP_IDLE",
	"ACT_OVERLAY_SHIELD_ATTACK",
	"ACT_OVERLAY_SHIELD_KNOCKBACK",
	"ACT_SHIELD_UP",
	"ACT_SHIELD_DOWN",
	"ACT_SHIELD_UP_IDLE",
	"ACT_SHIELD_ATTACK",
	"ACT_SHIELD_KNOCKBACK",
	"ACT_CROUCHING_SHIELD_UP",
	"ACT_CROUCHING_SHIELD_DOWN",
	"ACT_CROUCHING_SHIELD_UP_IDLE",
	"ACT_CROUCHING_SHIELD_ATTACK",
	"ACT_CROUCHING_SHIELD_KNOCKBACK",
	"ACT_TURNRIGHT45",
	"ACT_TURNLEFT45",
	"ACT_TURN",
	"ACT_OBJ_ASSEMBLING",
	"ACT_OBJ_DISMANTLING",
	"ACT_OBJ_STARTUP",
	"ACT_OBJ_RUNNING",
	"ACT_OBJ_IDLE",
	"ACT_OBJ_PLACING",
	"ACT_OBJ_DETERIORATING",
	"ACT_OBJ_UPGRADING",
	"ACT_DEPLOY",
	"ACT_DEPLOY_IDLE",
	"ACT_UNDEPLOY",
	"ACT_CROSSBOW_DRAW_UNLOADED",
	"ACT_GAUSS_SPINUP",
	"ACT_GAUSS_SPINCYCLE",
	"ACT_VM_PRIMARYATTACK_SILENCED",
	"ACT_VM_RELOAD_SILENCED",
	"ACT_VM_DRYFIRE_SILENCED",
	"ACT_VM_IDLE_SILENCED",
	"ACT_VM_DRAW_SILENCED",
	"ACT_VM_IDLE_EMPTY_LEFT",
	"ACT_VM_DRYFIRE_LEFT",
	"ACT_VM_IS_DRAW",
	"ACT_VM_IS_HOLSTER",
	"ACT_VM_IS_IDLE",
	"ACT_VM_IS_PRIMARYATTACK",
	"ACT_PLAYER_IDLE_FIRE",
	"ACT_PLAYER_CROUCH_FIRE",
	"ACT_PLAYER_CROUCH_WALK_FIRE",
	"ACT_PLAYER_WALK_FIRE",
	"ACT_PLAYER_RUN_FIRE",
	"ACT_IDLETORUN",
	"ACT_RUNTOIDLE",
	"ACT_VM_DRAW_DEPLOYED",
	"ACT_HL2MP_IDLE_MELEE",
	"ACT_HL2MP_RUN_MELEE",
	"ACT_HL2MP_IDLE_CROUCH_MELEE",
	"ACT_HL2MP_WALK_CROUCH_MELEE",
	"ACT_HL2MP_GESTURE_RANGE_ATTACK_MELEE",
	"ACT_HL2MP_GESTURE_RELOAD_MELEE",
	"ACT_HL2MP_JUMP_MELEE",
	"ACT_VM_FIZZLE",
	"ACT_MP_STAND_IDLE",
	"ACT_MP_CROUCH_IDLE",
	"ACT_MP_CROUCH_DEPLOYED_IDLE",
	"ACT_MP_CROUCH_DEPLOYED",
	"ACT_MP_DEPLOYED_IDLE",
	"ACT_MP_RUN",
	"ACT_MP_WALK",
	"ACT_MP_AIRWALK",
	"ACT_MP_CROUCHWALK",
	"ACT_MP_SPRINT",
	"ACT_MP_JUMP",
	"ACT_MP_JUMP_START",
	"ACT_MP_JUMP_FLOAT",
	"ACT_MP_JUMP_LAND",
	"ACT_MP_JUMP_IMPACT_N",
	"ACT_MP_JUMP_IMPACT_E",
	"ACT_MP_JUMP_IMPACT_W",
	"ACT_MP_JUMP_IMPACT_S",
	"ACT_MP_JUMP_IMPACT_TOP",
	"ACT_MP_DOUBLEJUMP",
	"ACT_MP_SWIM",
	"ACT_MP_DEPLOYED",
	"ACT_MP_SWIM_DEPLOYED",
	"ACT_MP_VCD",
	"ACT_MP_ATTACK_STAND_PRIMARYFIRE",
	"ACT_MP_ATTACK_STAND_PRIMARYFIRE_DEPLOYED",
	"ACT_MP_ATTACK_STAND_SECONDARYFIRE",
	"ACT_MP_ATTACK_STAND_GRENADE",
	"ACT_MP_ATTACK_CROUCH_PRIMARYFIRE",
	"ACT_MP_ATTACK_CROUCH_PRIMARYFIRE_DEPLOYED",
	"ACT_MP_ATTACK_CROUCH_SECONDARYFIRE",
	"ACT_MP_ATTACK_CROUCH_GRENADE",
	"ACT_MP_ATTACK_SWIM_PRIMARYFIRE",
	"ACT_MP_ATTACK_SWIM_SECONDARYFIRE",
	"ACT_MP_ATTACK_SWIM_GRENADE",
	"ACT_MP_ATTACK_AIRWALK_PRIMARYFIRE",
	"ACT_MP_ATTACK_AIRWALK_SECONDARYFIRE",
	"ACT_MP_ATTACK_AIRWALK_GRENADE",
	"ACT_MP_RELOAD_STAND",
	"ACT_MP_RELOAD_STAND_LOOP",
	"ACT_MP_RELOAD_STAND_END",
	"ACT_MP_RELOAD_CROUCH",
	"ACT_MP_RELOAD_CROUCH_LOOP",
	"ACT_MP_RELOAD_CROUCH_END",
	"ACT_MP_RELOAD_SWIM",
	"ACT_MP_RELOAD_SWIM_LOOP",
	"ACT_MP_RELOAD_SWIM_END",
	"ACT_MP_RELOAD_AIRWALK",
	"ACT_MP_RELOAD_AIRWALK_LOOP",
	"ACT_MP_RELOAD_AIRWALK_END",
	"ACT_MP_ATTACK_STAND_PREFIRE",
	"ACT_MP_ATTACK_STAND_POSTFIRE",
	"ACT_MP_ATTACK_STAND_STARTFIRE",
	"ACT_MP_ATTACK_CROUCH_PREFIRE",
	"ACT_MP_ATTACK_CROUCH_POSTFIRE",
	"ACT_MP_ATTACK_SWIM_PREFIRE",
	"ACT_MP_ATTACK_SWIM_POSTFIRE",
	"ACT_MP_STAND_PRIMARY",
	"ACT_MP_CROUCH_PRIMARY",
	"ACT_MP_RUN_PRIMARY",
	"ACT_MP_WALK_PRIMARY",
	"ACT_MP_AIRWALK_PRIMARY",
	"ACT_MP_CROUCHWALK_PRIMARY",
	"ACT_MP_JUMP_PRIMARY",
	"ACT_MP_JUMP_START_PRIMARY",
	"ACT_MP_JUMP_FLOAT_PRIMARY",
	"ACT_MP_JUMP_LAND_PRIMARY",
	"ACT_MP_SWIM_PRIMARY",
	"ACT_MP_DEPLOYED_PRIMARY",
	"ACT_MP_SWIM_DEPLOYED_PRIMARY",
	"ACT_MP_ATTACK_STAND_PRIMARY",
	"ACT_MP_ATTACK_STAND_PRIMARY_DEPLOYED",
	"ACT_MP_ATTACK_CROUCH_PRIMARY",
	"ACT_MP_ATTACK_CROUCH_PRIMARY_DEPLOYED",
	"ACT_MP_ATTACK_SWIM_PRIMARY",
	"ACT_MP_ATTACK_AIRWALK_PRIMARY",
	"ACT_MP_RELOAD_STAND_PRIMARY",
	"ACT_MP_RELOAD_STAND_PRIMARY_LOOP",
	"ACT_MP_RELOAD_STAND_PRIMARY_END",
	"ACT_MP_RELOAD_CROUCH_PRIMARY",
	"ACT_MP_RELOAD_CROUCH_PRIMARY_LOOP",
	"ACT_MP_RELOAD_CROUCH_PRIMARY_END",
	"ACT_MP_RELOAD_SWIM_PRIMARY",
	"ACT_MP_RELOAD_SWIM_PRIMARY_LOOP",
	"ACT_MP_RELOAD_SWIM_PRIMARY_END",
	"ACT_MP_RELOAD_AIRWALK_PRIMARY",
	"ACT_MP_RELOAD_AIRWALK_PRIMARY_LOOP",
	"ACT_MP_RELOAD_AIRWALK_PRIMARY_END",
	"ACT_MP_ATTACK_STAND_GRENADE_PRIMARY",
	"ACT_MP_ATTACK_CROUCH_GRENADE_PRIMARY",
	"ACT_MP_ATTACK_SWIM_GRENADE_PRIMARY",
	"ACT_MP_ATTACK_AIRWALK_GRENADE_PRIMARY",
	"ACT_MP_STAND_SECONDARY",
	"ACT_MP_CROUCH_SECONDARY",
	"ACT_MP_RUN_SECONDARY",
	"ACT_MP_WALK_SECONDARY",
	"ACT_MP_AIRWALK_SECONDARY",
	"ACT_MP_CROUCHWALK_SECONDARY",
	"ACT_MP_JUMP_SECONDARY",
	"ACT_MP_JUMP_START_SECONDARY",
	"ACT_MP_JUMP_FLOAT_SECONDARY",
	"ACT_MP_JUMP_LAND_SECONDARY",
	"ACT_MP_SWIM_SECONDARY",
	"ACT_MP_ATTACK_STAND_SECONDARY",
	"ACT_MP_ATTACK_CROUCH_SECONDARY",
	"ACT_MP_ATTACK_SWIM_SECONDARY",
	"ACT_MP_ATTACK_AIRWALK_SECONDARY",
	"ACT_MP_RELOAD_STAND_SECONDARY",
	"ACT_MP_RELOAD_STAND_SECONDARY_LOOP",
	"ACT_MP_RELOAD_STAND_SECONDARY_END",
	"ACT_MP_RELOAD_CROUCH_SECONDARY",
	"ACT_MP_RELOAD_CROUCH_SECONDARY_LOOP",
	"ACT_MP_RELOAD_CROUCH_SECONDARY_END",
	"ACT_MP_RELOAD_SWIM_SECONDARY",
	"ACT_MP_RELOAD_SWIM_SECONDARY_LOOP",
	"ACT_MP_RELOAD_SWIM_SECONDARY_END",
	"ACT_MP_RELOAD_AIRWALK_SECONDARY",
	"ACT_MP_RELOAD_AIRWALK_SECONDARY_LOOP",
	"ACT_MP_RELOAD_AIRWALK_SECONDARY_END",
	"ACT_MP_ATTACK_STAND_GRENADE_SECONDARY",
	"ACT_MP_ATTACK_CROUCH_GRENADE_SECONDARY",
	"ACT_MP_ATTACK_SWIM_GRENADE_SECONDARY",
	"ACT_MP_ATTACK_AIRWALK_GRENADE_SECONDARY",
	"ACT_MP_STAND_MELEE",
	"ACT_MP_CROUCH_MELEE",
	"ACT_MP_RUN_MELEE",
	"ACT_MP_WALK_MELEE",
	"ACT_MP_AIRWALK_MELEE",
	"ACT_MP_CROUCHWALK_MELEE",
	"ACT_MP_JUMP_MELEE",
	"ACT_MP_JUMP_START_MELEE",
	"ACT_MP_JUMP_FLOAT_MELEE",
	"ACT_MP_JUMP_LAND_MELEE",
	"ACT_MP_SWIM_MELEE",
	"ACT_MP_ATTACK_STAND_MELEE",
	"ACT_MP_ATTACK_STAND_MELEE_SECONDARY",
	"ACT_MP_ATTACK_CROUCH_MELEE",
	"ACT_MP_ATTACK_CROUCH_MELEE_SECONDARY",
	"ACT_MP_ATTACK_SWIM_MELEE",
	"ACT_MP_ATTACK_AIRWALK_MELEE",
	"ACT_MP_ATTACK_STAND_GRENADE_MELEE",
	"ACT_MP_ATTACK_CROUCH_GRENADE_MELEE",
	"ACT_MP_ATTACK_SWIM_GRENADE_MELEE",
	"ACT_MP_ATTACK_AIRWALK_GRENADE_MELEE",
	"ACT_MP_STAND_ITEM1",
	"ACT_MP_CROUCH_ITEM1",
	"ACT_MP_RUN_ITEM1",
	"ACT_MP_WALK_ITEM1",
	"ACT_MP_AIRWALK_ITEM1",
	"ACT_MP_CROUCHWALK_ITEM1",
	"ACT_MP_JUMP_ITEM1",
	"ACT_MP_JUMP_START_ITEM1",
	"ACT_MP_JUMP_FLOAT_ITEM1",
	"ACT_MP_JUMP_LAND_ITEM1",
	"ACT_MP_SWIM_ITEM1",
	"ACT_MP_ATTACK_STAND_ITEM1",
	"ACT_MP_ATTACK_STAND_ITEM1_SECONDARY",
	"ACT_MP_ATTACK_CROUCH_ITEM1",
	"ACT_MP_ATTACK_CROUCH_ITEM1_SECONDARY",
	"ACT_MP_ATTACK_SWIM_ITEM1",
	"ACT_MP_ATTACK_AIRWALK_ITEM1",
	"ACT_MP_STAND_ITEM2",
	"ACT_MP_CROUCH_ITEM2",
	"ACT_MP_RUN_ITEM2",
	"ACT_MP_WALK_ITEM2",
	"ACT_MP_AIRWALK_ITEM2",
	"ACT_MP_CROUCHWALK_ITEM2",
	"ACT_MP_JUMP_ITEM2",
	"ACT_MP_JUMP_START_ITEM2",
	"ACT_MP_JUMP_FLOAT_ITEM2",
	"ACT_MP_JUMP_LAND_ITEM2",
	"ACT_MP_SWIM_ITEM2",
	"ACT_MP_ATTACK_STAND_ITEM2",
	"ACT_MP_ATTACK_STAND_ITEM2_SECONDARY",
	"ACT_MP_ATTACK_CROUCH_ITEM2",
	"ACT_MP_ATTACK_CROUCH_ITEM2_SECONDARY",
	"ACT_MP_ATTACK_SWIM_ITEM2",
	"ACT_MP_ATTACK_AIRWALK_ITEM2",
	"ACT_MP_GESTURE_FLINCH",
	"ACT_MP_GESTURE_FLINCH_PRIMARY",
	"ACT_MP_GESTURE_FLINCH_SECONDARY",
	"ACT_MP_GESTURE_FLINCH_MELEE",
	"ACT_MP_GESTURE_FLINCH_ITEM1",
	"ACT_MP_GESTURE_FLINCH_ITEM2",
	"ACT_MP_GESTURE_FLINCH_HEAD",
	"ACT_MP_GESTURE_FLINCH_CHEST",
	"ACT_MP_GESTURE_FLINCH_STOMACH",
	"ACT_MP_GESTURE_FLINCH_LEFTARM",
	"ACT_MP_GESTURE_FLINCH_RIGHTARM",
	"ACT_MP_GESTURE_FLINCH_LEFTLEG",
	"ACT_MP_GESTURE_FLINCH_RIGHTLEG",
	"ACT_MP_GRENADE1_DRAW",
	"ACT_MP_GRENADE1_IDLE",
	"ACT_MP_GRENADE1_ATTACK",
	"ACT_MP_GRENADE2_DRAW",
	"ACT_MP_GRENADE2_IDLE",
	"ACT_MP_GRENADE2_ATTACK",
	"ACT_MP_PRIMARY_GRENADE1_DRAW",
	"ACT_MP_PRIMARY_GRENADE1_IDLE",
	"ACT_MP_PRIMARY_GRENADE1_ATTACK",
	"ACT_MP_PRIMARY_GRENADE2_DRAW",
	"ACT_MP_PRIMARY_GRENADE2_IDLE",
	"ACT_MP_PRIMARY_GRENADE2_ATTACK",
	"ACT_MP_SECONDARY_GRENADE1_DRAW",
	"ACT_MP_SECONDARY_GRENADE1_IDLE",
	"ACT_MP_SECONDARY_GRENADE1_ATTACK",
	"ACT_MP_SECONDARY_GRENADE2_DRAW",
	"ACT_MP_SECONDARY_GRENADE2_IDLE",
	"ACT_MP_SECONDARY_GRENADE2_ATTACK",
	"ACT_MP_MELEE_GRENADE1_DRAW",
	"ACT_MP_MELEE_GRENADE1_IDLE",
	"ACT_MP_MELEE_GRENADE1_ATTACK",
	"ACT_MP_MELEE_GRENADE2_DRAW",
	"ACT_MP_MELEE_GRENADE2_IDLE",
	"ACT_MP_MELEE_GRENADE2_ATTACK",
	"ACT_MP_ITEM1_GRENADE1_DRAW",
	"ACT_MP_ITEM1_GRENADE1_IDLE",
	"ACT_MP_ITEM1_GRENADE1_ATTACK",
	"ACT_MP_ITEM1_GRENADE2_DRAW",
	"ACT_MP_ITEM1_GRENADE2_IDLE",
	"ACT_MP_ITEM1_GRENADE2_ATTACK",
	"ACT_MP_ITEM2_GRENADE1_DRAW",
	"ACT_MP_ITEM2_GRENADE1_IDLE",
	"ACT_MP_ITEM2_GRENADE1_ATTACK",
	"ACT_MP_ITEM2_GRENADE2_DRAW",
	"ACT_MP_ITEM2_GRENADE2_IDLE",
	"ACT_MP_ITEM2_GRENADE2_ATTACK",
	"ACT_MP_STAND_BUILDING",
	"ACT_MP_CROUCH_BUILDING",
	"ACT_MP_RUN_BUILDING",
	"ACT_MP_WALK_BUILDING",
	"ACT_MP_AIRWALK_BUILDING",
	"ACT_MP_CROUCHWALK_BUILDING",
	"ACT_MP_JUMP_BUILDING",
	"ACT_MP_JUMP_START_BUILDING",
	"ACT_MP_JUMP_FLOAT_BUILDING",
	"ACT_MP_JUMP_LAND_BUILDING",
	"ACT_MP_SWIM_BUILDING",
	"ACT_MP_ATTACK_STAND_BUILDING",
	"ACT_MP_ATTACK_CROUCH_BUILDING",
	"ACT_MP_ATTACK_SWIM_BUILDING",
	"ACT_MP_ATTACK_AIRWALK_BUILDING",
	"ACT_MP_ATTACK_STAND_GRENADE_BUILDING",
	"ACT_MP_ATTACK_CROUCH_GRENADE_BUILDING",
	"ACT_MP_ATTACK_SWIM_GRENADE_BUILDING",
	"ACT_MP_ATTACK_AIRWALK_GRENADE_BUILDING",
	"ACT_MP_STAND_PDA",
	"ACT_MP_CROUCH_PDA",
	"ACT_MP_RUN_PDA",
	"ACT_MP_WALK_PDA",
	"ACT_MP_AIRWALK_PDA",
	"ACT_MP_CROUCHWALK_PDA",
	"ACT_MP_JUMP_PDA",
	"ACT_MP_JUMP_START_PDA",
	"ACT_MP_JUMP_FLOAT_PDA",
	"ACT_MP_JUMP_LAND_PDA",
	"ACT_MP_SWIM_PDA",
	"ACT_MP_ATTACK_STAND_PDA",
	"ACT_MP_ATTACK_SWIM_PDA",
	"ACT_MP_GESTURE_VC_HANDMOUTH",
	"ACT_MP_GESTURE_VC_FINGERPOINT",
	"ACT_MP_GESTURE_VC_FISTPUMP",
	"ACT_MP_GESTURE_VC_THUMBSUP",
	"ACT_MP_GESTURE_VC_NODYES",
	"ACT_MP_GESTURE_VC_NODNO",
	"ACT_MP_GESTURE_VC_HANDMOUTH_PRIMARY",
	"ACT_MP_GESTURE_VC_FINGERPOINT_PRIMARY",
	"ACT_MP_GESTURE_VC_FISTPUMP_PRIMARY",
	"ACT_MP_GESTURE_VC_THUMBSUP_PRIMARY",
	"ACT_MP_GESTURE_VC_NODYES_PRIMARY",
	"ACT_MP_GESTURE_VC_NODNO_PRIMARY",
	"ACT_MP_GESTURE_VC_HANDMOUTH_SECONDARY",
	"ACT_MP_GESTURE_VC_FINGERPOINT_SECONDARY",
	"ACT_MP_GESTURE_VC_FISTPUMP_SECONDARY",
	"ACT_MP_GESTURE_VC_THUMBSUP_SECONDARY",
	"ACT_MP_GESTURE_VC_NODYES_SECONDARY",
	"ACT_MP_GESTURE_VC_NODNO_SECONDARY",
	"ACT_MP_GESTURE_VC_HANDMOUTH_MELEE",
	"ACT_MP_GESTURE_VC_FINGERPOINT_MELEE",
	"ACT_MP_GESTURE_VC_FISTPUMP_MELEE",
	"ACT_MP_GESTURE_VC_THUMBSUP_MELEE",
	"ACT_MP_GESTURE_VC_NODYES_MELEE",
	"ACT_MP_GESTURE_VC_NODNO_MELEE",
	"ACT_MP_GESTURE_VC_HANDMOUTH_ITEM1",
	"ACT_MP_GESTURE_VC_FINGERPOINT_ITEM1",
	"ACT_MP_GESTURE_VC_FISTPUMP_ITEM1",
	"ACT_MP_GESTURE_VC_THUMBSUP_ITEM1",
	"ACT_MP_GESTURE_VC_NODYES_ITEM1",
	"ACT_MP_GESTURE_VC_NODNO_ITEM1",
	"ACT_MP_GESTURE_VC_HANDMOUTH_ITEM2",
	"ACT_MP_GESTURE_VC_FINGERPOINT_ITEM2",
	"ACT_MP_GESTURE_VC_FISTPUMP_ITEM2",
	"ACT_MP_GESTURE_VC_THUMBSUP_ITEM2",
	"ACT_MP_GESTURE_VC_NODYES_ITEM2",
	"ACT_MP_GESTURE_VC_NODNO_ITEM2",
	"ACT_MP_GESTURE_VC_HANDMOUTH_BUILDING",
	"ACT_MP_GESTURE_VC_FINGERPOINT_BUILDING",
	"ACT_MP_GESTURE_VC_FISTPUMP_BUILDING",
	"ACT_MP_GESTURE_VC_THUMBSUP_BUILDING",
	"ACT_MP_GESTURE_VC_NODYES_BUILDING",
	"ACT_MP_GESTURE_VC_NODNO_BUILDING",
	"ACT_MP_GESTURE_VC_HANDMOUTH_PDA",
	"ACT_MP_GESTURE_VC_FINGERPOINT_PDA",
	"ACT_MP_GESTURE_VC_FISTPUMP_PDA",
	"ACT_MP_GESTURE_VC_THUMBSUP_PDA",
	"ACT_MP_GESTURE_VC_NODYES_PDA",
	"ACT_MP_GESTURE_VC_NODNO_PDA",
	"ACT_VM_UNUSABLE",
	"ACT_VM_UNUSABLE_TO_USABLE",
	"ACT_VM_USABLE_TO_UNUSABLE",
	"ACT_PRIMARY_VM_DRAW",
	"ACT_PRIMARY_VM_HOLSTER",
	"ACT_PRIMARY_VM_IDLE",
	"ACT_PRIMARY_VM_PULLBACK",
	"ACT_PRIMARY_VM_PRIMARYATTACK",
	"ACT_PRIMARY_VM_SECONDARYATTACK",
	"ACT_PRIMARY_VM_RELOAD",
	"ACT_PRIMARY_VM_DRYFIRE",
	"ACT_PRIMARY_VM_IDLE_TO_LOWERED",
	"ACT_PRIMARY_VM_IDLE_LOWERED",
	"ACT_PRIMARY_VM_LOWERED_TO_IDLE",
	"ACT_SECONDARY_VM_DRAW",
	"ACT_SECONDARY_VM_HOLSTER",
	"ACT_SECONDARY_VM_IDLE",
	"ACT_SECONDARY_VM_PULLBACK",
	"ACT_SECONDARY_VM_PRIMARYATTACK",
	"ACT_SECONDARY_VM_SECONDARYATTACK",
	"ACT_SECONDARY_VM_RELOAD",
	"ACT_SECONDARY_VM_DRYFIRE",
	"ACT_SECONDARY_VM_IDLE_TO_LOWERED",
	"ACT_SECONDARY_VM_IDLE_LOWERED",
	"ACT_SECONDARY_VM_LOWERED_TO_IDLE",
	"ACT_MELEE_VM_DRAW",
	"ACT_MELEE_VM_HOLSTER",
	"ACT_MELEE_VM_IDLE",
	"ACT_MELEE_VM_PULLBACK",
	"ACT_MELEE_VM_PRIMARYATTACK",
	"ACT_MELEE_VM_SECONDARYATTACK",
	"ACT_MELEE_VM_RELOAD",
	"ACT_MELEE_VM_DRYFIRE",
	"ACT_MELEE_VM_IDLE_TO_LOWERED",
	"ACT_MELEE_VM_IDLE_LOWERED",
	"ACT_MELEE_VM_LOWERED_TO_IDLE",
	"ACT_PDA_VM_DRAW",
	"ACT_PDA_VM_HOLSTER",
	"ACT_PDA_VM_IDLE",
	"ACT_PDA_VM_PULLBACK",
	"ACT_PDA_VM_PRIMARYATTACK",
	"ACT_PDA_VM_SECONDARYATTACK",
	"ACT_PDA_VM_RELOAD",
	"ACT_PDA_VM_DRYFIRE",
	"ACT_PDA_VM_IDLE_TO_LOWERED",
	"ACT_PDA_VM_IDLE_LOWERED",
	"ACT_PDA_VM_LOWERED_TO_IDLE",
	"ACT_ITEM1_VM_DRAW",
	"ACT_ITEM1_VM_HOLSTER",
	"ACT_ITEM1_VM_IDLE",
	"ACT_ITEM1_VM_PULLBACK",
	"ACT_ITEM1_VM_PRIMARYATTACK",
	"ACT_ITEM1_VM_SECONDARYATTACK",
	"ACT_ITEM1_VM_RELOAD",
	"ACT_ITEM1_VM_DRYFIRE",
	"ACT_ITEM1_VM_IDLE_TO_LOWERED",
	"ACT_ITEM1_VM_IDLE_LOWERED",
	"ACT_ITEM1_VM_LOWERED_TO_IDLE",
	"ACT_ITEM2_VM_DRAW",
	"ACT_ITEM2_VM_HOLSTER",
	"ACT_ITEM2_VM_IDLE",
	"ACT_ITEM2_VM_PULLBACK",
	"ACT_ITEM2_VM_PRIMARYATTACK",
	"ACT_ITEM2_VM_SECONDARYATTACK",
	"ACT_ITEM2_VM_RELOAD",
	"ACT_ITEM2_VM_DRYFIRE",
	"ACT_ITEM2_VM_IDLE_TO_LOWERED",
	"ACT_ITEM2_VM_IDLE_LOWERED",
	"ACT_ITEM2_VM_LOWERED_TO_IDLE",
	"ACT_RELOAD_SUCCEED",
	"ACT_RELOAD_FAIL",
	"ACT_WALK_AIM_AUTOGUN",
	"ACT_RUN_AIM_AUTOGUN",
	"ACT_IDLE_AUTOGUN",
	"ACT_IDLE_AIM_AUTOGUN",
	"ACT_RELOAD_AUTOGUN",
	"ACT_CROUCH_IDLE_AUTOGUN",
	"ACT_RANGE_ATTACK_AUTOGUN",
	"ACT_JUMP_AUTOGUN",
	"ACT_IDLE_AIM_PISTOL",
	"ACT_WALK_AIM_DUAL",
	"ACT_RUN_AIM_DUAL",
	"ACT_IDLE_DUAL",
	"ACT_IDLE_AIM_DUAL",
	"ACT_RELOAD_DUAL",
	"ACT_CROUCH_IDLE_DUAL",
	"ACT_RANGE_ATTACK_DUAL",
	"ACT_JUMP_DUAL",
	"ACT_IDLE_SHOTGUN",
	"ACT_IDLE_AIM_SHOTGUN",
	"ACT_CROUCH_IDLE_SHOTGUN",
	"ACT_JUMP_SHOTGUN",
	"ACT_IDLE_AIM_RIFLE",
	"ACT_RELOAD_RIFLE",
	"ACT_CROUCH_IDLE_RIFLE",
	"ACT_RANGE_ATTACK_RIFLE",
	"ACT_JUMP_RIFLE",
	"ACT_SLEEP",
	"ACT_WAKE",
	"ACT_FLICK_LEFT",
	"ACT_FLICK_LEFT_MIDDLE",
	"ACT_FLICK_RIGHT_MIDDLE",
	"ACT_FLICK_RIGHT",
	"ACT_SPINAROUND",
	"ACT_PREP_TO_FIRE",
	"ACT_FIRE",
	"ACT_FIRE_RECOVER",
	"ACT_SPRAY",
	"ACT_PREP_EXPLODE",
	"ACT_EXPLODE",
	"ACT_DOTA_IDLE",
	"ACT_DOTA_RUN",
	"ACT_DOTA_ATTACK",
	"ACT_DOTA_ATTACK_EVENT",
	"ACT_DOTA_DIE",
	"ACT_DOTA_FLINCH",
	"ACT_DOTA_DISABLED",
	"ACT_DOTA_CAST_ABILITY_1",
	"ACT_DOTA_CAST_ABILITY_2",
	"ACT_DOTA_CAST_ABILITY_3",
	"ACT_DOTA_CAST_ABILITY_4",
	"ACT_DOTA_OVERRIDE_ABILITY_1",
	"ACT_DOTA_OVERRIDE_ABILITY_2",
	"ACT_DOTA_OVERRIDE_ABILITY_3",
	"ACT_DOTA_OVERRIDE_ABILITY_4",
	"ACT_DOTA_CHANNEL_ABILITY_1",
	"ACT_DOTA_CHANNEL_ABILITY_2",
	"ACT_DOTA_CHANNEL_ABILITY_3",
	"ACT_DOTA_CHANNEL_ABILITY_4",
	"ACT_DOTA_CHANNEL_END_ABILITY_1",
	"ACT_DOTA_CHANNEL_END_ABILITY_2",
	"ACT_DOTA_CHANNEL_END_ABILITY_3",
	"ACT_DOTA_CHANNEL_END_ABILITY_4",
	"ACT_MP_RUN_SPEEDPAINT",
	"ACT_MP_LONG_FALL",
	"ACT_MP_TRACTORBEAM_FLOAT",
	"ACT_MP_DEATH_CRUSH",
	"ACT_MP_RUN_SPEEDPAINT_PRIMARY",
	"ACT_MP_DROWNING_PRIMARY",
	"ACT_MP_LONG_FALL_PRIMARY",
	"ACT_MP_TRACTORBEAM_FLOAT_PRIMARY",
	"ACT_MP_DEATH_CRUSH_PRIMARY",
	"ACT_DIE_STAND",
	"ACT_DIE_STAND_HEADSHOT",
	"ACT_DIE_CROUCH",
	"ACT_DIE_CROUCH_HEADSHOT",
	"ACT_CSGO_NULL",
	"ACT_CSGO_DEFUSE",
	"ACT_CSGO_DEFUSE_WITH_KIT",
	"ACT_CSGO_FLASHBANG_REACTION",
	"ACT_CSGO_FIRE_PRIMARY",
	"ACT_CSGO_FIRE_PRIMARY_OPT_1",
	"ACT_CSGO_FIRE_PRIMARY_OPT_2",
	"ACT_CSGO_FIRE_SECONDARY",
	"ACT_CSGO_FIRE_SECONDARY_OPT_1",
	"ACT_CSGO_FIRE_SECONDARY_OPT_2",
	"ACT_CSGO_RELOAD",
	"ACT_CSGO_RELOAD_START",
	"ACT_CSGO_RELOAD_LOOP",
	"ACT_CSGO_RELOAD_END",
	"ACT_CSGO_OPERATE",
	"ACT_CSGO_DEPLOY",
	"ACT_CSGO_CATCH",
	"ACT_CSGO_SILENCER_DETACH",
	"ACT_CSGO_SILENCER_ATTACH",
	"ACT_CSGO_TWITCH",
	"ACT_CSGO_TWITCH_BUYZONE",
	"ACT_CSGO_PLANT_BOMB",
	"ACT_CSGO_IDLE_TURN_BALANCEADJUST",
	"ACT_CSGO_IDLE_ADJUST_STOPPEDMOVING",
	"ACT_CSGO_ALIVE_LOOP",
	"ACT_CSGO_FLINCH",
	"ACT_CSGO_FLINCH_HEAD",
	"ACT_CSGO_FLINCH_MOLOTOV",
	"ACT_CSGO_JUMP",
	"ACT_CSGO_FALL",
	"ACT_CSGO_CLIMB_LADDER",
	"ACT_CSGO_LAND_LIGHT",
	"ACT_CSGO_LAND_HEAVY",
	"ACT_CSGO_EXIT_LADDER_TOP",
	"ACT_CSGO_EXIT_LADDER_BOTTOM",
};

char Util::GetButtonString(ButtonCode_t key)
{
	switch (key)
	{
		case KEY_PAD_0:
			return '0';
		case KEY_PAD_1:
			return '1';
		case KEY_PAD_2:
			return '2';
		case KEY_PAD_3:
			return '3';
		case KEY_PAD_4:
			return '4';
		case KEY_PAD_5:
			return '5';
		case KEY_PAD_6:
			return '6';
		case KEY_PAD_7:
			return '7';
		case KEY_PAD_8:
			return '8';
		case KEY_PAD_9:
			return '9';
		case KEY_PAD_DIVIDE:
			return '/';
		case KEY_PAD_MULTIPLY:
			return '*';
		case KEY_PAD_MINUS:
			return '-';
		case KEY_PAD_PLUS:
			return '+';
		case KEY_SEMICOLON:
			return ';';
		default:
			return inputSystem->ButtonCodeToString(key)[0];
	}
}

std::string Util::GetButtonName(ButtonCode_t buttonCode)
{
	return inputSystem->ButtonCodeToString(buttonCode);
}

ButtonCode_t Util::GetButtonCode(std::string buttonName)
{
	for (int i = 0; i < ButtonCode_t::KEY_XSTICK2_UP; i++)
	{
		const char* currentButton = inputSystem->ButtonCodeToString((ButtonCode_t) i);
		if (strcmp(currentButton, buttonName.c_str()) == 0)
			return (ButtonCode_t) i;
	}

	return ButtonCode_t::BUTTON_CODE_INVALID;
}

IMaterial* Util::CreateMaterial(std::string type, std::string texture, bool ignorez, bool nofog, bool model, bool nocull, bool halflambert)
{
	static int matNum = 1;
	std::stringstream materialData;
	materialData << "\"" + type + "\"\n"
			"{\n"
			"\t\"$basetexture\" \"" + texture + "\"\n"
			"\t\"$ignorez\" \"" + std::to_string(ignorez) + "\"\n"
			"\t\"$nofog\" \"" + std::to_string(nofog) + "\"\n"
			"\t\"$model\" \"" + std::to_string(model) + "\"\n"
			"\t\"$nocull\" \"" + std::to_string(nocull) + "\"\n"
			"\t\"$halflambert\" \"" + std::to_string(halflambert) + "\"\n"
			"}\n" << std::flush;

    char randomLetter = 'a' + rand()%26;
	std::string time = randomLetter + std::string( __TIME__ ); // compile time XX:XX:XX
	time.erase( std::remove(time.begin(), time.end(), ':'), time.end() ); // remove colons
	std::string materialName = time + "_" + std::to_string( matNum );
    cvar->ConsoleDPrintf("MatName: %s\n", materialName.c_str());
	matNum++;

	KeyValues* keyValues = new KeyValues(materialName.c_str());
	InitKeyValues(keyValues, type.c_str());
	LoadFromBuffer(keyValues, materialName.c_str(), materialData.str().c_str(), nullptr, nullptr, nullptr);

	return material->CreateMaterial(materialName.c_str(), keyValues);
}

const char* Util::GetActivityName(int actNum) {
	if( actNum == -1 ){
		return "ACT_INVALID";
	}
	return ActivityStrings[actNum];
}

bool Util::IsDangerZone()
{
	return (gameTypes->GetCurrentGameType() == 6);
}