/* Writen by Alex Luong
 * Test CDA class */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cda.h"
#include "integer.h"

static void displayItems(CDA *);
static void visualizeItems(CDA *);
static void testInsertAndRemove(CDA *);
static void testSetAndGet(CDA *);
static void testUnion(CDA *, CDA *);
static void testExtract(CDA *);

int main(void) {
  int i;
  CDA *items = newCDA(displayInteger);
  testInsertAndRemove(items);

  // Currently, items = [][1]
  testSetAndGet(items);

  // Set up recipient and donor
  CDA *recipient = newCDA(displayInteger);
  for (i = 0; i < 4; i++)
    insertCDAback(recipient, newInteger(i));

  CDA *donor = newCDA(displayInteger);
  for (i = 0; i < 5; i++)
    insertCDAback(donor, newInteger(i));

  // Test union
  testUnion(recipient, donor);

  testExtract(recipient);

  return 0;
}

static void testInsertAndRemove(CDA *items) {
  int i;

  // Display an empty DA
  displayItems(items);

  printf("\n");

  // Put 100 values in the array
  for (i = 0; i < 50; i++)
    insertCDAback(items, newInteger(i));
  for (i = 50; i < 100; i++)
    insertCDAfront(items, newInteger(i));
  displayItems(items);
  visualizeItems(items);
  printf("\n");

  // Remove the last value
  printf("The value ");
  displayInteger(stdout, removeCDAback(items));
  printf(" was removed.\n");
  printf("\n");

  // Remove the first value
  printf("The value ");
  displayInteger(stdout, removeCDAfront(items));
  printf(" was removed.\n");
  printf("\n");

  // Remove the rest
  for (i = 0; i < 49; i++)
    removeCDAback(items);
  for (i = 0; i < 49; i++)
    removeCDAfront(items);
  displayItems(items);
  visualizeItems(items);
  printf("\n");
}

static void testSetAndGet(CDA *items) {
  insertCDAback(items, newInteger(1));
  visualizeItems(items);
  int x = getInteger((integer *) getCDA(items,0));
  printf("The first item is %d.\n", x);
  setCDA(items, 0, newInteger(2));
  printf("After set:\n");
  visualizeItems(items);
  printf("\n");
}

static void testUnion(CDA *recipient, CDA *donor) {
  // Union
  unionCDA(recipient, donor);

  // Show donor
  printf("Donor:\n");
  displayItems(donor);
  visualizeItems(donor);
  printf("\n");

  // Show recipient
  printf("Recipient:\n");
  displayItems(recipient);
  visualizeItems(recipient);
  printf("\n");
}

static void testExtract(CDA *items) {
  // Extract
  int size = sizeCDA(items);
  void **array = extractCDA(items);
  printf("Recipient after extracting:\n");
  visualizeItems(items);
  printf("\n");

  printf("The last item in the extracted array is %d\n", getInteger((integer *)array[size-1]));
}

static void displayItems(CDA *items) {
  printf("displayItems: ");
  displayCDA(stdout,items);
  printf("\n");
}

static void visualizeItems(CDA *items) {
  printf("visualizeItems: ");
  visualizeCDA(stdout,items);
  printf("\n");
}