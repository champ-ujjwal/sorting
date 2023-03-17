public static void getFcmTokenApi(Context context, String username, List<Integer> serviceProviderIdList, String phone, int userId, NotificationItems notificationItems)
{

    // pass -11 to service provider id and user id, when it is not required

    Paper.init(context);

    // don't declare the requestQueue here , it should be in onCreate method
    RequestQueue requestQueue = Volley.newRequestQueue(context);

    String url = context.getResources().getString(R.string.database_url) + "v1/api/getfcmtoken";

    JSONObject jsonObject = new JSONObject();
    HashMap<String, Object> hashMap = new HashMap<>();

    try
    {
        if (userId != -11)
            jsonObject.put("user_id", userId);
        else if (phone != null)
            jsonObject.put("phone", phone);
        else if (serviceProviderIdList != null)
        {

            JSONArray jsArray = new JSONArray(serviceProviderIdList);
            jsonObject.put("serviceprovider_id", jsArray);
        }
        else if (username != null)
            jsonObject.put("username", username);
    }
    catch (JSONException e)
    {
        Log.d("pError1221", "exception in getfcmtoken api " + e);
        e.printStackTrace();
    }

    //    JSONObject jsonObject = new JSONObject(hashMap);

    Log.d("pRequestBody", "getfcmtoken request body : " + jsonObject);

    JsonObjectRequest jsonObjectRequest = new JsonObjectRequest(
        Request.Method.POST, url, jsonObject,
        new Response.Listener<JSONObject>() {
            @Override public void onResponse(JSONObject response)
            {
                //    progressBarDialog.dismiss(); // close the progressbar
                Log.d("pResponse", "getfcmtoken response : " + response.toString());

                try
                {
                    if (response.getBoolean("status"))
                    {

                        if (response.has("token_list"))
                        {
                            ArrayList<String> tokenList = new ArrayList<>();
                            JSONArray jsonArray = response.getJSONArray("token_list");

                            for (int i = 0; i < jsonArray.length(); i++)
                            {
                                JSONObject jsonObject1 = jsonArray.getJSONObject(i);
                                String fcmToken = jsonObject1.getString("fcmtoken");
                                if (fcmToken.equals("null"))
                                    continue;
                                tokenList.add(fcmToken);

                                sendMultipleNotificationApi(context, notificationItems, tokenList);
                            }
                        }
                        else
                        {
                            String fcmToken = response.getString("fcm_token");

                            notificationItems.setFcmToken(fcmToken);

                            sendNotificationApi(context, notificationItems);
                        }
                    }
                }
                catch (JSONException e)
                {

                    e.printStackTrace();
                }
            }
        },
        new Response.ErrorListener() {
            @Override public void onErrorResponse(VolleyError error)
            {

                Log.d("pError339", "error while saving fcm token in getfcmtoken api " + error);
            }
        })

    {
        @Override public Map<String, String> getHeaders() throws AuthFailureError
        {
            Map<String, String> params = new HashMap<String, String>();

            // instead o f pass current user authtoken
            //             params.put("authtoken", Paper.book().read("authToken"));
            //
            params.put("authtoken", Paper.book().read("authToken"));

            return params;
        }
    };

    jsonObjectRequest.setRetryPolicy(new DefaultRetryPolicy(
        6000,
        DefaultRetryPolicy.DEFAULT_MAX_RETRIES,
        DefaultRetryPolicy.DEFAULT_BACKOFF_MULT));

    requestQueue.add(jsonObjectRequest);
}