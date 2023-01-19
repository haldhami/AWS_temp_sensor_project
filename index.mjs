import { DynamoDBClient } from "@aws-sdk/client-dynamodb";
import {
  DynamoDBDocumentClient,
  ScanCommand,
  PutCommand,
  GetCommand,
  DeleteCommand,
} from "@aws-sdk/lib-dynamodb";

const client = new DynamoDBClient({});

const dynamo = DynamoDBDocumentClient.from(client);

const tableName = "Sensor_Data";

export const handler = async (event, context) => {
  let body;
  let statusCode = 200;
  const headers = {
    "Content-Type": "application/json",
  };

  try {
    switch (event.routeKey) {
      case "DELETE /items/{time}":
        await dynamo.send(
          new DeleteCommand({
            TableName: tableName,
            Key: {
              time: event.pathParameters.time,
            },
          })
        );
        body = `Deleted item ${event.pathParameters.time}`;
        break;
      case "GET /items/{time}":
        body = await dynamo.send(
          new GetCommand({
            TableName: tableName,
            Key: {
              time: event.pathParameters.time,
            },
          })
        );
        body = body.Item;
        break;
      case "GET /items":
        body = await dynamo.send(
          new ScanCommand({ TableName: tableName })
        );
        body = body.Items;
        break;
      case "PUT /items":
        let requestJSON = JSON.parse(event.body);
        await dynamo.send(
          new PutCommand({
            TableName: tableName,
            Item: {
              time: requestJSON.time,
              temp_in: requestJSON.temp_in,
              temp_out: requestJSON.temp_out,
            },
          })
        );
        body = `Put item ${requestJSON.time}`;
        break;
      default:
        throw new Error(`Unsupported route: "${event.routeKey}"`);
    }
  } catch (err) {
    statusCode = 400;
    body = err.message;
  } finally {
    body = JSON.stringify(body);
  }

  return {
    statusCode,
    body,
    headers,
  };
};
