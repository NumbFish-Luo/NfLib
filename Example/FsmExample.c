#include <stdio.h>
#include <string.h>
#include "FsmExample.h"

#include <NfLib/Base/Base.h>
#include <NfLib/Fsm/FsmCfg.h> // 【暂时】在这里修改状态机设置
#include <NfLib/Fsm/Fsm.h>

#pragma warning(disable:4996) // vs2019

static u8 testNodeVal = 0;
static void Call_NodeA(void) { testNodeVal = 1; }
static void Call_NodeB(void) { testNodeVal = 2; }
static void Call_NodeC(void) { testNodeVal = 3; }

static u8 testLineVal = 0;
static void Call_Line1(void) { testLineVal = 1; }
static void Call_Line2(void) { testLineVal = 2; }
static void Call_Line3(void) { testLineVal = 3; }

void Fsm_Example(void) {
    char eventNameStr[16] = { "FsmLine_None" };
    FsmEventName eventName = FsmLine_None;

    static FsmNode nodeA, nodeB, nodeC;
    static FsmLine line1, line2, line3;
    static Fsm fsm;

    //        Line1         Line2         Line3
    // NodeA ------> NodeB ------> NodeC ------> NodeA
    FsmNode_Init(&nodeA, FsmNode_A, Call_NodeA);
    FsmNode_Init(&nodeB, FsmNode_B, Call_NodeB);
    FsmNode_Init(&nodeC, FsmNode_C, Call_NodeC);

    FsmLine_Init(&line1, &nodeA, &nodeB, FsmLine_1, Call_Line1);
    FsmLine_Init(&line2, &nodeB, &nodeC, FsmLine_2, Call_Line2);
    FsmLine_Init(&line3, &nodeC, &nodeA, FsmLine_3, Call_Line3);

    // AddNode, AddLine
    Fsm_Init(&fsm);

    fsm.ops->AddNode(&fsm, &nodeA);
    fsm.ops->AddNode(&fsm, &nodeB);
    fsm.ops->AddNode(&fsm, &nodeC);

    fsm.ops->AddLine(&fsm, &line1);
    fsm.ops->AddLine(&fsm, &line2);
    fsm.ops->AddLine(&fsm, &line3);

    // Set start node
    fsm.ops->Start(&fsm, FsmNode_A);

    // Handle event
    do {
             if (strcmp(eventNameStr, ToStr(FsmLine_1)) == 0) { eventName = FsmLine_1; }
        else if (strcmp(eventNameStr, ToStr(FsmLine_2)) == 0) { eventName = FsmLine_2; }
        else if (strcmp(eventNameStr, ToStr(FsmLine_3)) == 0) { eventName = FsmLine_3; }
        else                                                  { eventName = FsmLine_None; }

        fsm.ops->HandleEvent(&fsm, eventName); // 处理事件

        printf("testNodeVal = %d, testLineVal = %d, currNodeName = %d\n\n\
Please enter the event name :-P >> ",
            testNodeVal, testLineVal, fsm.currNode->name);
    } while (scanf("%s", eventNameStr) != EOF);

    /* Example input & output >>
        testNodeVal = 1, testLineVal = 0, currNodeName = 1

        Please enter the event name :-P >> FsmLine_1
        testNodeVal = 2, testLineVal = 1, currNodeName = 2

        Please enter the event name :-P >> FsmLine_2
        testNodeVal = 3, testLineVal = 2, currNodeName = 3

        Please enter the event name :-P >> FsmLine_3
        testNodeVal = 1, testLineVal = 3, currNodeName = 1

        Please enter the event name :-P >> FsmLine_None
        testNodeVal = 1, testLineVal = 3, currNodeName = 1

        Please enter the event name :-P >> FsmLine_2
        testNodeVal = 1, testLineVal = 3, currNodeName = 1

        Please enter the event name :-P >> FsmLine_1
        testNodeVal = 2, testLineVal = 1, currNodeName = 2

        Please enter the event name :-P >> 
    */
}
