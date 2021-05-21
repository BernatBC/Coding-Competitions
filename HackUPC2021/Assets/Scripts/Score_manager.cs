using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Score_manager : MonoBehaviour
{
    public static Score_manager score_manager;
    public Text scoreboard;
    private int score = 0;

    private void Start()
    {
        score_manager = this;
    }

    public void Add_score(int s) {
        score += s;
        scoreboard.text = score.ToString();
    }

    public int Score() {
        int a = score;
        score = 0;
        return a;
    }
}
