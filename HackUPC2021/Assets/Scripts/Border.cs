using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Border : MonoBehaviour
{
    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.tag == "Player")
        {
            Debug.Log("Exit");
            PlayerController.playerController.EndGame();
        }
        else {
            Destroy(collision.gameObject, 0.5f);
        }
    }
}
