using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Scene_manager : MonoBehaviour
{
    public Texture2D cursor;
    
    public void Play() {
        SceneManager.LoadScene("SampleScene");
        Cursor.SetCursor(cursor, Vector2.zero, CursorMode.Auto);
    }

    public void Highscore() {
        SceneManager.LoadScene("Highscorepage");
        Cursor.SetCursor(null, Vector2.zero, CursorMode.Auto);
    }

    public void Controls()
    {
        SceneManager.LoadScene("Controlspage");
        Cursor.SetCursor(null, Vector2.zero, CursorMode.Auto);
    }

    public void Main()
    {
        SceneManager.LoadScene("Mainpage");
        Cursor.SetCursor(null, Vector2.zero, CursorMode.Auto);
    }

    public void About() {
        SceneManager.LoadScene("About");
        Cursor.SetCursor(null, Vector2.zero, CursorMode.Auto);
    }
}
